/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/05 21:57:44 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO pipes

/// @brief Check and apply redirection in input.
/// @param *input String of the prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	check_redirection(char *input, t_prompt *prompt, t_garbage *garbage)
{
	int	pos;

	pos = -1;
	if (get_separator_pos(input, "<") != -1 && \
		pos <= get_separator_pos(input, "<"))
		pos = get_separator_pos(input, "<");
	if (get_separator_pos(input, ">") != -1 && \
		pos <= get_separator_pos(input, ">"))
		pos = get_separator_pos(input, ">");
	if (pos != -1)
	{
		if (input[pos] == '>')
			set_output(input + pos, prompt, garbage);
		if (input[pos] == '<')
			set_input(input + pos, prompt, garbage);
	}
}

/// @brief Append output of cmd to end of file.
/// @param *input String of the prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	set_output_append(char *input, t_prompt *prompt, t_garbage *garbage)
{
	int		i;
	char	*name;

	i = get_char_pos(input, '>');
	while (input[i] && (input[i] == '>' || isspace(input[i])))
		i++;
	if (!input[i])
		return ((void)printf("Parsing error around >\n"));
	input += i;
	while (get_char_pos(input, '$') != -1)
		check_is_env_var(&input, garbage);
	name = ft_strsep(&input, " ");
	prompt->old_stdout = dup(1);
	close(1);
	prompt->write_fd = open(name, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (prompt->write_fd == -1)
	{
		printf("Error in opening file, set redirection to error output\n");
		dup2(prompt->old_stdout, STDOUT_FILENO);
	}
}

/// @brief Reset fd 1 to stdout.
/// @param *prompt Pointer to prompt struct.
void	reset_stdio_fd(t_prompt *prompt)
{
	if (prompt->write_fd == -1)
		return ;
	close(prompt->write_fd);
	if (prompt->old_stdout != -1)
	{	
		dup2(prompt->old_stdout, 1);
		close(prompt->old_stdout);
	}
	if (prompt->old_stdin != -1)
	{
		dup2(prompt->old_stdin, 0);
		close(prompt->old_stdin);
	}
}
