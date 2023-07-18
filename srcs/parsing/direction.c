/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/18 10:50:43 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//TODO cat text0.txt > output.txt text1.txt
//	is the same as doing 'cat text0.txt text1.txt > output.txt


void	check_redirection(char *input, t_prompt *prompt, t_garbage *garbage)
{
	if (get_char_pos(input, '>') != -1)
		set_output(input, prompt, garbage);
}

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
	close(prompt->write_fd);
	dup2(prompt->old_stdout, 1);
	close(prompt->old_stdout);
}
