/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:34:30 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/23 19:21:13 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_exec(t_prompt *prompt, int i)
{
	if (ft_strcmp(prompt->full_args[i]->s, ";") && \
		ft_strcmp(prompt->full_args[i]->s, "|"))
		return (1);
	return (0);
}

int	exec_child(t_prompt *prompt, int i, t_garbage *garbage)
{
	dup2(prompt->exec_fd[1], STDOUT_FILENO);
	close(prompt->exec_fd[1]);
	close(prompt->exec_fd[0]);
	if (is_builtin(prompt->full_args[0]->s))
		exec_builtin(prompt, garbage);
	else if (ft_execute(prompt->full_args, i, prompt->tmp_fd,
			prompt->environ))
		return (0);
	return (1);
}

int	redir(t_prompt *prompt)
{
	check_redirection(prompt);
	if (prompt->has_redir == -1)
	{
		close(prompt->exec_fd[1]);
		close(prompt->tmp_fd);
		prompt->tmp_fd = prompt->exec_fd[0];
		return (0);
	}
	delete_redirection(prompt->full_args);
	return (1);
}

void	wait_exec(t_prompt *prompt, int value)
{
	close(prompt->tmp_fd);
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
}