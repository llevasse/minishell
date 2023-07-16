/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/16 22:54:04 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirection(char *input, t_prompt *prompt, t_garbage *garbage)
{
	if (get_char_pos(input, '>') != -1)
		set_output(input, prompt);
//	if (get_char_pos(input, '<') != -1)
//	
//	if (get_char_pos(input, '|') != -1)
	(void)garbage;
}

void	set_output(char *input, t_prompt *prompt)
{
	int			i;

	printf("sa race : |%s|\n", input);
	i = get_char_pos(input, '>');
	if (input[i + 1] == '>')
		return (set_output_append(input, prompt));
	while (input[i] && (input[i] == '>' || isspace(input[i])))
		i++;
	if (!input[i])
		return ((void)printf("Parsing error around >\n"));
	prompt->old_stdout = dup(1);
	close(1);
	prompt->write_fd = open(ft_strsep(&input + i, " "), O_RDWR | O_TRUNC | O_CREAT, 0666);
	printf("Opened file at fd : %d", prompt->write_fd);	
	if (prompt->write_fd == -1)
	{
		printf("Error in opening file, set redirection to error output\n");
		dup2(prompt->old_stdout, STDOUT_FILENO);
	}
}

void	set_output_append(char *input, t_prompt *prompt)
{
	int	i;	

	i = get_char_pos(input, '>');
	while (input[i] && input[i] == '>' && isspace(input[i]))
		i++;
	if (!input[i])
		return ((void)printf("Parsing error around >\n"));
	
	prompt->write_fd = open(ft_strsep(&input, " "), O_RDWR | O_APPEND | O_CREAT, 0666);
	if (prompt->write_fd == -1)
	{
		printf("Error in opening file, set redirection to error output\n");
		prompt->write_fd = 2;
	}
}
