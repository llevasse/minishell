/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/22 14:41:13 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle input redirection in prompt.
/// Close stdin fd and assign to input file fd 0, 
/// So that execve will write into it.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	set_input(char *input, t_prompt *prompt, t_garbage *garbage)
{
	int			i;
	char		*name;

	i = get_char_pos(input, '<');
	if (input[i + 1] == '<')
		return (heredoc(input, prompt, garbage));
	while (input[i] && (input[i] == '<' || isspace(input[i])))
		i++;
	if (!input[i])
		return ((void)printf("Parsing error around <\n"));
	input += i;
	while (get_char_pos(input, '$') != -1)
		check_is_env_var(&input, garbage);
	name = ft_strsep(&input, " ");
	prompt->old_stdin = dup(0);
	prompt->write_fd = open(name, O_RDONLY);
	dup2(prompt->write_fd, STDIN_FILENO);
	if (prompt->write_fd == -1)
	{
		printf("Error in opening file, set redirection to error output\n");
		dup2(prompt->old_stdin, STDOUT_FILENO);
	}
}


/// @brief Get outin redirection args ("> {file_name}")
/// @param *input Prompt input,
/// @param *garbage Pointer to garbage collector.
/// @return Return a string in the format "> {file_name}"
char	*get_input(char *input_prompt, t_garbage *garbage)
{
	char	*input;
	int		i;
	int		j;
	
	i = get_char_pos(input_prompt, '<');
	j = 0;
	while (input_prompt[i + j] && (input_prompt[i + j] == '<' || ft_isspace(input_prompt[i + j])))
		j++;
	while (input_prompt[i + j] && !ft_isspace(input_prompt[i + j]))
		j++;
	input = malloc((j + 1) * sizeof(char));
	ft_add_garbage(&garbage, input);
	ft_strlcpy(input, input_prompt + i, j + 1);
	return (input);	
}

/// @brief Handle multiple output in prompt.
/// Rerun check_cmd with one output redirection removed, 
/// recursivly, until all output have been filled.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	multiple_input(char *input_prompt, t_prompt *prompt, t_garbage *garbage)
{
	char		*input;
	char		*dup_input_prompt;	
	t_prompt	*new_prompt;
	
	new_prompt = malloc(sizeof(struct s_prompt));
	ft_add_garbage(&garbage, new_prompt);
	input = get_input(input_prompt, garbage);
	dup_input_prompt = ft_strdup(input_prompt);
	replace_str(&dup_input_prompt, input, "", garbage);
	new_prompt->write_fd = -1;
	new_prompt->d_quotes = prompt->d_quotes;
	new_prompt->quotes = prompt->d_quotes;
	new_prompt->args = NULL;
	new_prompt->export_args = NULL;
	new_prompt->cmd = prompt->cmd;
	get_args(new_prompt, dup_input_prompt, garbage);
	check_redirection(dup_input_prompt, new_prompt, garbage);
	check_cmd(new_prompt, garbage);
	replace_str(&input_prompt, get_input(dup_input_prompt, garbage), "", garbage);
	parse_args(NULL, prompt->args, NULL);
}
