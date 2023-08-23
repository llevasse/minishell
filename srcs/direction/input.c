/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/23 19:15:01 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle input redirection in prompt.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	set_input(char *name, t_prompt *prompt)
{
	int	fd;
	int	entry_errno;

	entry_errno = errno;
	if (!name)
	{
		errno = 2;
		write(2, ERR_PARSE_INPUT, ft_strlen(ERR_PARSE_INPUT));
		return ((void)(prompt->cmd = 0));
	}
	if (name[0] == '<')
		name++;
	fd = open(name, O_RDONLY);
	if (fd == -1 && entry_errno != 2)
	{
		prompt->has_redir = -1;
		return ((void)(write(2, NO_FILE_E, ft_strlen(NO_FILE_E))));
	}
	dup2(fd, prompt->tmp_fd);
	close(fd);
	prompt->has_redir = 1;
}
