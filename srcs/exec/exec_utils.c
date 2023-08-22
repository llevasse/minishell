/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:36:58 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/22 21:44:31 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_fd(t_prompt *prompt)
{
	prompt->next_cmd->tmp_fd = prompt->tmp_fd;
	prompt->next_cmd->old_stdout = prompt->old_stdout;
	prompt->next_cmd->old_stdin = prompt->old_stdin;
	prompt->next_cmd->exec_fd[0] = prompt->exec_fd[0];
	prompt->next_cmd->exec_fd[1] = prompt->exec_fd[1];
}

int	cmp_exec(t_prompt *prompt, int i)
{
	if (ft_strcmp(prompt->full_args[i]->s, ";") && \
		ft_strcmp(prompt->full_args[i]->s, "|"))
		return (1);
	else
		return (0);
}

void	wait_exec(t_prompt *prompt, int value)
{
	close(prompt->tmp_fd);
	waitpid(prompt->exec_pid, &value, WUNTRACED);
	if (WIFEXITED(value))
		errno = WEXITSTATUS(value);
}
