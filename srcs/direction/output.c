/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/23 13:29:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if file to output from does not exist programm breaks

/// @brief Handle output redirection in prompt.
/// @param *prompt Pointer to prompt struct,
void	set_output(t_prompt *prompt)
{
	int			fd;

	fd = get_last_output_fd(prompt->args);
	if (fd == -1)
		return ((void)(errno = 2, prompt->cmd = 0, prompt->has_redir = -1));
	if (prompt->exec_fd[1] != -1)
		dup2(fd, prompt->exec_fd[1]);
	else
	{
		prompt->old_stdout = dup(1);
		dup2(fd, 1);
	}
	close(fd);
	prompt->has_redir = 1;
	prompt->has_output = 1;
}

int	do_open(char *name, int append, int to_close)
{
	int	fd;

	if (to_close != -1)
		close(to_close);
	if (!name)
		write(2, ERR_PARSE_OUTPUT, ft_strlen(ERR_PARSE_OUTPUT));
	if (append)
		fd = open(name, O_RDWR | O_APPEND | O_CREAT, 0666);
	else
		fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 0666);
	return (fd);
}

/// @brief Get index of file name to write into in an array of strings.
/// @param **args Array of strings containing
/// each element of shell input separated.
/// @return Return Index of where the name of file to write in
/// or -1 if none are found 
/// (or an error occured).
int	get_last_output_fd(t_arg **args)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (args[i])
	{
		if (args[i]->quote == 0 && args[i]->s[0] == '>')
		{
			if (args[i]->s[1] == '>' && args[i]->s[2])
				fd = do_open(args[i]->s + 2, 1, fd);
			else if (args[i]->s[1] == '>' && args[i]->s[2] == 0 && args[i + 1])
				fd = do_open(args[i + 1]->s, 1, fd);
			else if (args[i]->s[1] == '>' && args[i]->s[2] == 0 && !args[i + 1])
				fd = do_open(NULL, 0, fd);
			else if (args[i]->s[1] && args[i]->s[1] != '>')
				fd = do_open(args[i]->s + 1, 0, fd);
			else if (args[i]->s[1] == 0 && args[i + 1])
				fd = do_open(args[i + 1]->s, 0, fd);
			else if (args[i]->s[1] == 0 && !args[i + 1])
				fd = do_open(NULL, 0, fd);
		}
		i++;
	}
	return (fd);
}
