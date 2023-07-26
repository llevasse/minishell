/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/26 21:32:33 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/// @brief Handle output redirection in prompt.
/// Close stdout fd and assign to output file fd 1, 
/// So that execve will write into it.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	set_output(char *input, t_prompt *prompt, t_garbage *garbage)
{
	int			i;
	char		*name;

	i = get_char_pos(input, '>');
	if (input[i + 1] == '>')
		return (set_output_append(input, prompt, garbage));
	while (input[i] && (input[i] == '>' || isspace(input[i])))
		i++;
	if (!input[i])
		return ((void)printf("Parsing error around >\n"));
	if (get_char_pos(input + i, '>') != -1)
		multiple_output(input, prompt, garbage);
	input += i;
	while (get_char_pos(input, '$') != -1)
		check_is_env_var(&input, garbage);
	name = ft_strsep(&input, " ");
	prompt->old_stdout = dup(1);
	close(1);
	prompt->write_fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (prompt->write_fd == -1)
	{
		printf("Error in opening file, set redirection to error output\n");
		dup2(prompt->old_stdout, STDOUT_FILENO);
	}
}

/// @brief Get output redirection args ("> {file_name}")
/// @param *input Prompt input,
/// @param *garbage Pointer to garbage collector.
/// @return Return a string in the format "> {file_name}"
char	*get_output(char *input, t_garbage *garbage)
{
	char	*output;
	int		i;
	int		j;
	
	i = get_char_pos(input, '>');
	j = 0;
	while (input[i + j] && (input[i + j] == '>' || ft_isspace(input[i + j])))
		j++;
	while (input[i + j] && !ft_isspace(input[i + j]))
		j++;
	output = malloc((j + 1) * sizeof(char));
	ft_add_garbage(0, &garbage, output);
	ft_strlcpy(output, input + i, j + 1);
	return (output);	
}

/// @brief Handle multiple output in prompt.
/// Rerun check_cmd with one output redirection removed, 
/// recursivly, until all output have been filled.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	multiple_output(char *input, t_prompt *prompt, t_garbage *garbage)
{
	char		*output;
	char		*dup_input;	
	t_prompt	*new_prompt;
	
	new_prompt = malloc(sizeof(struct s_prompt));
	ft_add_garbage(0, &garbage, new_prompt);
	output = get_output(input, garbage);
	dup_input = ft_strdup(input);
	replace_str(&dup_input, output, "", garbage);
	new_prompt->write_fd = -1;
	new_prompt->d_quotes = prompt->d_quotes;
	new_prompt->quotes = prompt->d_quotes;
	new_prompt->args = NULL;
	new_prompt->export_args = NULL;
	new_prompt->cmd = prompt->cmd;
	get_args(new_prompt, dup_input, garbage);
	check_redirection(dup_input, new_prompt, garbage);
	check_cmd(new_prompt, garbage);
	replace_str(&input, get_output(dup_input, garbage), "", garbage);
	parse_args(NULL, prompt->args, NULL);
}
