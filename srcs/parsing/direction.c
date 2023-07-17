/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:50:13 by mwubneh           #+#    #+#             */
/*   Updated: 2023/07/17 14:50:29 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/17 13:22:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <ctype.h>

//TODO pass environment variable content as file name 
// ex : cat srcs/minishell.c > $USER
// will print the outpur of cat in a file named after the content of $USER


void	check_redirection(char *input, t_prompt *prompt, t_garbage *garbage)
{
	if (get_char_pos(input, '>') != -1)
		set_output(input, prompt);
	(void)garbage;
}

void	set_output(char *input, t_prompt *prompt)
{
	int			i;
	char		*name;

	i = get_char_pos(input, '>');
	if (input[i + 1] == '>')
		return (set_output_append(input, prompt));
	while (input[i] && (input[i] == '>' || isspace(input[i])))
		i++;
	if (!input[i])
		return ((void)printf("Parsing error around >\n"));
	input += i;
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

void	set_output_append(char *input, t_prompt *prompt)
{
	int	i;	

	i = get_char_pos(input, '>');
	while (input[i] && input[i] == '>' && isspace(input[i]))
		i++;
	if (!input[i])
		return ((void)printf("Parsing error around >\n"));
	prompt->write_fd = open(ft_strsep(&input, " "),
			O_RDWR | O_APPEND | O_CREAT, 0666);
	if (prompt->write_fd == -1)
	{
		printf("Error in opening file, set redirection to error output\n");
		prompt->write_fd = 2;
	}
}

void	reset_stdio_fd(t_prompt *prompt)
{
	close(prompt->write_fd);
	dup2(prompt->old_stdout, 1);
	close(prompt->old_stdout);
}
