/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:34:30 by mwubneh           #+#    #+#             */
/*   Updated: 2023/09/03 13:36:34 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_child(t_prompt *prompt)
{
	dup2(prompt->exec_fd[1], STDOUT_FILENO);
	do_close(&prompt->exec_fd[1]);
	do_close(&prompt->exec_fd[0]);
	if (is_builtin(prompt->full_args[0]->s))
	{
		exec_builtin(prompt);
		close(1);
		ft_exit(prompt->shell, NULL);
	}
	else if (ft_execute(prompt->full_args, prompt->tmp_fd,
			prompt->shell))
		return (0);
	return (1);
}

int	redir(t_prompt *prompt)
{
	check_redirection(prompt);
	if (prompt->has_redir <= -1)
	{
		do_close(&prompt->exec_fd[1]);
		do_close(&prompt->tmp_fd);
		prompt->tmp_fd = prompt->exec_fd[0];
		if (prompt->has_redir == -2)
		{
			do_close(&prompt->exec_fd[0]);
			do_close(&prompt->old_stdin);
			do_close(&prompt->old_stdout);
			pre_parse(prompt->heredoc_last_input, prompt->shell);
			parse(prompt->heredoc_last_input, prompt->garbage, prompt->shell);
		}
		return (0);
	}
	delete_redirection(prompt->full_args);
	return (1);
}

void	wait_exec(t_prompt *prompt, int value)
{
	if (prompt->exec_pid != -1)
	{
		waitpid(prompt->exec_pid, &value, WUNTRACED);
		if (WIFEXITED(value))
			errno = WEXITSTATUS(value);
		else if (WIFSIGNALED(value))
		{
			if (WTERMSIG(value) == SIGQUIT)
			{
				write(1, ERR_QUIT, 21);
				errno = 131;
			}
			if (WTERMSIG(value) == SIGINT)
				errno = 130;
		}
	}
	else if (prompt->exec_fd[0] != -1)
		do_close(&prompt->exec_fd[0]);
}

void	swap_fd(t_prompt *prompt)
{
	do_close(&prompt->exec_fd[1]);
	do_close(&prompt->tmp_fd);
	prompt->next_cmd->tmp_fd = prompt->exec_fd[0];
	prompt->next_cmd->old_stdout = prompt->old_stdout;
	prompt->next_cmd->old_stdin = prompt->old_stdin;
	prompt->next_cmd->exec_fd[0] = prompt->exec_fd[0];
	prompt->next_cmd->exec_fd[1] = prompt->exec_fd[1];
}
