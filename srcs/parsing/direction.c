/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/19 23:34:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO redirection input

//TODO heredoc

void	check_redirection(char *input, t_prompt *prompt, t_garbage *garbage)
{
	if (get_char_pos(input, '>') != -1)
		set_output(input, prompt, garbage);
}



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

void	reset_stdio_fd(t_prompt *prompt)
{
	if (prompt->write_fd >= 0)
		close(prompt->write_fd);
	dup2(prompt->old_stdout, 1);
	if (prompt->old_stdout >= 0)
		close(prompt->old_stdout);
}
