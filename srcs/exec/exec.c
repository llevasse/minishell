/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/25 11:12:00 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static int	get_exec(t_prompt *prompt, int i, t_garbage *garbage);
static int	get_exec_pipe(t_prompt *prompt, int i, t_garbage *garbage);
static void	pls_wait(t_prompt *prompt);

void	exec(t_prompt *prompt, t_garbage *garbage)
{
	int			i;
	t_prompt	*temp;

	i = 0;
	prompt->tmp_fd = dup(STDIN_FILENO);
	temp = prompt;
	while (prompt->full_args && prompt->full_args[i])
	{
		while (prompt->full_args[i] && cmp_exec(prompt, i))
			i++;
		if (i != 0 && (prompt->full_args[i] == NULL || \
				!ft_strcmp(prompt->full_args[i]->s, ";")))
			get_exec(prompt, i, garbage);
		else if (i != 0 && !ft_strcmp(prompt->full_args[i]->s, "|"))
			get_exec_pipe (prompt, i, garbage);
		if (prompt->has_exec && prompt->next_cmd)
		{
			swap_fd(prompt);
			prompt = prompt->next_cmd;
			i = 0;
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
		{
			wait_exec(prompt, value);
		}
		else
		{
			wait_exec(prompt, value);
			prompt->tmp_fd = dup(STDIN_FILENO);
			break ;
		}
		prompt = prompt->next_cmd;
	}
	close(prompt->tmp_fd);
}

static int	get_exec(t_prompt *prompt, int i, t_garbage *garbage)
{
	check_redirection(prompt);
	if (!redir(prompt) || !prompt->cmd)
		return ((void)(prompt->has_exec = 1), 1);
	delete_redirection(prompt->full_args);
	if (!prompt->next_cmd && !prompt->prev_cmd && \
				!ft_strcmp(prompt->cmd, "exit"))
		ft_exit(garbage, prompt->full_args);
	if (exec_builtin_main_thread(prompt, garbage))
		return (0);
	prompt->exec_pid = fork();
	if (prompt->exec_pid == 0)
	{
		reset_termios();
		if (prompt->prev_cmd)
			prompt->tmp_fd = dup(prompt->exec_fd[0]);
		if (is_builtin(prompt->full_args[0]->s))
			exec_builtin(prompt, garbage);
		else if (ft_execute(prompt->full_args, i, prompt->tmp_fd,
				prompt->environ))
			return (1);
	}
	else
	{
		if (prompt->exec_fd[0] != -1)
			close(prompt->exec_fd[0]);
		close(prompt->tmp_fd);
		prompt->has_exec = 1;
	}
	return (0);
}

static int	get_exec_pipe(t_prompt *prompt, int i, t_garbage *garbage)
{
	exec_builtin_main_thread(prompt, garbage);
	if (pipe(prompt->exec_fd) == -1)
	{
		free_garbage(garbage);
		return ((void)(write(2, PIPE_ERR, ft_strlen(PIPE_ERR))), 1);
	}
	if (!redir(prompt) || !prompt->cmd)
		return ((void)(prompt->has_exec = 1), 1);
	if (prompt->has_redir == 1)
		i = get_arg_size(prompt->args) + 1;
	prompt->exec_pid = fork();
	if (prompt->exec_pid == 0)
	{
		dup2(prompt->exec_fd[1], STDOUT_FILENO);
		close(prompt->exec_fd[1]);
		close(prompt->exec_fd[0]);
		reset_termios();
		if (!exec_child(prompt, i, garbage))
			return (1);
	}
	else
	{
		prompt->has_exec = 1;
		close(prompt->exec_fd[1]);
		close(prompt->tmp_fd);
		prompt->tmp_fd = prompt->exec_fd[0];
	}
	return (0);
}

int	ft_execute(t_arg **args, int i, int tmp_fd, char **envp)
{
	char	**c_args;

	if (args[i])
		args[i]->s = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	c_args = to_char_array(args, i, g_minishell.garbage);
	execve(c_args[0], c_args, envp);
	ft_putstr_fd("error : cannot execute ", 2);
	ft_putendl_fd(c_args[0], 2);
	return (1);
}
