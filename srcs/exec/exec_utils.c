/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:34:30 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/21 23:36:56 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_prompt *prompt, int value)
{
	waitpid(prompt->exec_pid, &value, WUNTRACED);
	if (WIFEXITED(value))
		errno = WEXITSTATUS(value);
}

void	swap_fd(t_prompt *prompt)
{
	prompt->next_cmd->tmp_fd = prompt->tmp_fd;
	prompt->next_cmd->old_stdout = prompt->old_stdout;
	prompt->next_cmd->old_stdin = prompt->old_stdin;
	prompt->next_cmd->exec_fd[0] = prompt->exec_fd[0];
	prompt->next_cmd->exec_fd[1] = prompt->exec_fd[1];
	prompt = prompt->next_cmd;
}
