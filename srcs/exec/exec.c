/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/09/03 10:40:57 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exec(t_prompt *prompt);
static int	get_exec_pipe(t_prompt *prompt);
static void	pls_wait(t_prompt *prompt);

void	exec(t_prompt *prompt)
{
	int			i;
	t_prompt	*temp;

	i = 0;
	prompt->tmp_fd = dup(0);
	temp = prompt;
	while (prompt->full_args && prompt->full_args[0])
	{
		if (!prompt->next_cmd)
			get_exec(prompt);
		else
			get_exec_pipe (prompt);
		if (prompt->has_redir == -2)
			return ;
		else if (prompt->has_exec && prompt->next_cmd)
			prompt = next_prompt(prompt);
		else
		{
			do_close(&prompt->exec_fd[0]);
			prompt->tmp_fd = -1;
			break ;
		}
	}
	pls_wait(temp);
}

static void	pls_wait(t_prompt *prompt)
{
	int			value;

	value = 0;
	while (prompt)
	{
		if (prompt->next_cmd)
			wait_exec(prompt, value);
		else
		{
			wait_exec(prompt, value);
			do_close(&prompt->tmp_fd);
			prompt->tmp_fd = dup(STDIN_FILENO);
			break ;
		}
		prompt = prompt->next_cmd;
	}
}

static int	get_exec(t_prompt *prompt)
{
	sig_init(prompt);
	if (prompt->prev_cmd && (prompt->prev_cmd->has_redir > 0) && \
		prompt->prev_cmd->exec_pid != -1)
		kill(prompt->prev_cmd->exec_pid, SIGUSR1);
	if (!redir(prompt) || !prompt->cmd)
		return ((void)(prompt->has_exec = 1), 1);
	if (!is_builtin(prompt->cmd))
		prompt->exec_pid = fork();
	if (prompt->exec_pid == 0)
		return (child_exec(prompt));
	else
	{
		if (is_builtin(prompt->cmd))
			exec_builtin(prompt);
		sig_mute(prompt);
		if (prompt->exec_fd[0] != -1)
			prompt->tmp_fd = dup(prompt->exec_fd[0]);
	}
	return ((void)(prompt->has_exec = 1), 0);
}

static int	get_exec_pipe(t_prompt *prompt)
{
	if (prompt->prev_cmd && (prompt->prev_cmd->has_redir > 0) && \
		prompt->prev_cmd->exec_pid != -1)
		kill(prompt->prev_cmd->exec_pid, SIGUSR1);
	if (pipe(prompt->exec_fd) == -1)
	{
		free_garbage(prompt->garbage);
		return ((void)(write(2, PIPE_ERR, ft_strlen(PIPE_ERR))), 1);
	}
	if (!redir(prompt) || !prompt->cmd)
		return ((void)(prompt->has_exec = 1), 1);
	if (!is_builtin(prompt->cmd))
		prompt->exec_pid = fork();
	if (prompt->exec_pid == 0 || is_builtin(prompt->cmd))
	{
		if (!prompt->has_redir)
			do_close(&prompt->exec_fd[0]);
		reset_termios();
		if (is_builtin(prompt->cmd))
			exec_child(prompt);
		if (prompt->exec_pid == 0 && !exec_child(prompt))
			return (1);
	}
	return ((void)(prompt->has_exec = 1), 0);
}

int	ft_execute(t_arg **args, int tmp_fd, t_minishell *shell)
{
	char	**c_args;

	dup2(tmp_fd, STDIN_FILENO);
	do_close(&tmp_fd);
	c_args = to_char_array(args, shell);
	execve(c_args[0], c_args, shell->env);
	ft_putstr_fd("error : cannot execute ", 2);
	ft_putendl_fd(c_args[0], 2);
	return (1);
}
