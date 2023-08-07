/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/07 23:38:33 by llevasse         ###   ########.fr       */
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
	int			fd;

	i = get_char_pos(input, '<');
	if (input[i + 1] == '<')
		return (heredoc(input, prompt, garbage));
	while (input[i] && (input[i] == '<' || isspace(input[i])))
		i++;
	if (!input[i])
		return ((void)printf("Parsing error around <\n"));
	if (get_char_pos(input + i, '<') != -1)
		multiple_input(input, prompt, garbage);
	input += i;
	while (get_char_pos(input, '$') != -1)
		check_is_env_var(&input, garbage);
	name = ft_strsep(&input, " ");
	if (create_heredoc_fd(prompt) == -1)
		return ;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return ((void)(printf("Error in opening file\n"), prompt->cmd = NULL));
	write_file_to_fd(fd, prompt->heredoc_fd[1], garbage);
}

void	write_file_to_fd(int fd_to_read, int fd_to_write, t_garbage *garbage)
{
	char	*str;

	str = get_next_line(fd_to_read);
	while (str)
	{	
		ft_add_garbage(0, &garbage, str);
		ft_putstr_fd(str, fd_to_write);
		str = get_next_line(fd_to_read);
	}
	close(fd_to_read);
}

/// @brief Get outin redirection args ("< {file_name}")
/// @param *input Prompt input,
/// @param *garbage Pointer to garbage collector.
/// @return Return a string in the format "< {file_name}"
char	*get_input(char *input_prompt, t_garbage *garbage)
{
	char	*input;
	int		i;
	int		j;

	i = get_char_pos(input_prompt, '<');
	j = 0;
	while (input_prompt[i + j] && \
	(input_prompt[i + j] == '<' || ft_isspace(input_prompt[i + j])))
		j++;
	while (input_prompt[i + j] && !ft_isspace(input_prompt[i + j]))
		j++;
	input = malloc((j + 1) * sizeof(char));
	ft_add_garbage(0, &garbage, input);
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
	ft_add_garbage(0, &garbage, new_prompt);
	input = get_input(input_prompt, garbage);
	dup_input_prompt = ft_strdup(input_prompt);
	replace_str(&dup_input_prompt, input, "", garbage);
	new_prompt->write_fd = -1;
	new_prompt->d_quotes = prompt->d_quotes;
	new_prompt->quotes = prompt->d_quotes;
	new_prompt->args = NULL;
	new_prompt->export_args = NULL;
	new_prompt->cmd = prompt->cmd;
	new_prompt->next_cmd = NULL;
	get_args(new_prompt, dup_input_prompt, garbage);
	check_redirection(dup_input_prompt, new_prompt, garbage);
	ft_add_prompt(&prompt, new_prompt);
	replace_str(&input_prompt, input, "", garbage);
}
