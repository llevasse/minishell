/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/08 17:06:39 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle output redirection in prompt.
/// Close stdout fd and assign to output file fd 1, 
/// So that execve will write into it.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	set_output(t_prompt *prompt)
{
	int			i;
	int			fd;

	i = get_last_output_index(prompt->args);
	if (i == -1)
		return ;
	if (!prompt->args[i])
		return ((void)printf("Parsing error around >\n"));
	if (prompt->old_stdout == -1)
		prompt->old_stdout = dup(1);
	if (!ft_strcmp(prompt->args[i - 1],">>"))
		fd = open(prompt->args[i], O_RDWR | O_APPEND | O_CREAT, 0666);
	else
		fd = open(prompt->args[i], O_RDWR | O_TRUNC | O_CREAT, 0666);
	prompt->write_fd = fd;
	dup2(prompt->write_fd, 1);
	if (prompt->write_fd == -1)
	{
		printf("Error in opening file, set redirection to error output\n");
		dup2(prompt->old_stdout, STDOUT_FILENO);
	}
}

int	get_last_output_index(char **args)
{
	int	i;
	int	j;
	int	fd;

	i = 0;
	j = -1;
	while (args[i])
	{
		if (!ft_strcmp(">", args[i]) || !ft_strcmp(">>", args[i]))
		{
			if (args[i + 1])
			{
				if (!ft_strcmp(">>", args[i]))
					fd = open(args[i + 1], O_RDWR | O_APPEND | O_CREAT, 0666);
				else
					fd = open(args[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
				if (fd != -1)
					close(fd);
			}
			j = i;
		}
		i++;
	}
	if (j == -1)
		return (-1);
	return (j + 1);
}
