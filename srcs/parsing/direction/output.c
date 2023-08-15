/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/15 22:38:31 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if file to output from does not exist programm breaks

/// @brief Handle output redirection in prompt.
/// @param *prompt Pointer to prompt struct,
void	set_output(t_prompt *prompt)
{
	int			i;
	int			fd;

	i = get_last_output_index(prompt->args);
	if (i == -1)
		return ((void)(errno = 2, prompt->cmd = 0));
	if (!prompt->args[i])
		return ((void)printf(ERR_PARSE_OUTPUT));
	if (prompt->old_stdout == -1)
		prompt->old_stdout = dup(1);
	if (!ft_strcmp(prompt->args[i - 1], ">>"))
		fd = open(prompt->args[i], O_RDWR | O_APPEND | O_CREAT, 0666);
	else
		fd = open(prompt->args[i], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (prompt->write_fd == -1)
		printf(ERR_OPEN_F);
	prompt->write_fd = fd;
	dup2(prompt->write_fd, 1);
}

/// @brief Open and close file to verify it's existence and/or create it.
/// @param **args Array of strings containing
/// each element of shell input separated,
/// @param index Index of element to open.
void	tini_tiny_open(char **args, int index)
{
	int	fd;

	if (!ft_strcmp(">>", args[index - 1]))
		fd = open(args[index], O_RDWR | O_APPEND | O_CREAT, 0666);
	else
		fd = open(args[index], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd != -1)
		close(fd);
}

/// @brief Get index of file name to write into in an array of strings.
/// @param **args Array of strings containing
/// each element of shell input separated.
/// @return Return Index of where the name of file to write in
/// or -1 if none are found 
/// (or an error occured).
int	get_last_output_index(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (args[i])
	{
		if (!ft_strcmp(">", args[i++]) || !ft_strcmp(">>", args[i - 1]))
		{
			if (args[i])
				tini_tiny_open(args, i);
			else
			{
				errno = 2;
				return ((void)(printf(ERR_PARSE_OUTPUT)), -1);
			}
			j = i - 1;
		}
	}
	if (j == -1)
		return (-1);
	return (j + 1);
}
