/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/21 10:31:35 by llevasse         ###   ########.fr       */
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
	{
		errno = 2;
		write(2, ERR_PARSE_INPUT, ft_strlen(ERR_PARSE_INPUT));
		return ((void)(prompt->cmd = 0));
	}
	if (prompt->heredoc_fd[0] != -1)
	{
		close(prompt->heredoc_fd[0]);
		close(prompt->heredoc_fd[1]);
		prompt->heredoc_fd[0] = -1;
	}
	if (name[0] == '<')
		name++;
	if (create_heredoc_fd(prompt) == -1)
		return ;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return ((void)(write(2, NO_FILE, ft_strlen(NO_FILE))));
	dup2(fd, prompt->heredoc_fd[0]);
	close(fd);
	(void)garbage;
}
