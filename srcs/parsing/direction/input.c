/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/08 22:49:16 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle input redirection in prompt.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	set_input(char *name, t_prompt *prompt, t_garbage *garbage)
{
	int			fd;

	if (!name)
		return ((void)(prompt->cmd = 0));
	if (prompt->heredoc_fd[0] != -1)
	{
		close(prompt->heredoc_fd[0]);
		close(prompt->heredoc_fd[1]);
		prompt->heredoc_fd[0] = -1;
	}
	if (create_heredoc_fd(prompt) == -1)
		return ;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return ((void)(printf("%s: No such file or directory\n", name)));
	write_file_to_fd(fd, prompt->heredoc_fd[1], garbage);
}

/// @brief Write content of file from fd_to_read to fd_to_write.
/// @param fd_to_read Fd of file to read from,
/// @param fd_to_write Fd of file to write into,
/// @param *garbage Pointer to garbage collector.
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
