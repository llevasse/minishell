/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/15 23:25:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char			**environ;
extern t_minishell	g_minishell;

static int	get_exec(t_prompt *prompt, int i, int value, t_garbage *garbage);
static int	get_exec_pipe(t_prompt *prompt, int i, int value, t_garbage *garbage);
static int	ft_putstr_error(char *str, char *arg);
static int	ft_execute(char **args, int i, int tmp_fd, char **envp);

void	exec(t_prompt *prompt, t_garbage *garbage)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	prompt->tmp_fd = dup(STDIN_FILENO);
	while (prompt->full_args[i])
	{
		if (i != 0 && prompt->full_args[i + 1])
		{
			prompt->full_args = &prompt->full_args[i + 1];
			i = 0;
		}
		while (prompt->full_args[i] && \
				ft_strcmp(prompt->full_args[i], ";") && \
					ft_strcmp(prompt->full_args[i], "|"))
			i++;
		if (i != 0 && (prompt->full_args[i] == NULL || \
				!ft_strcmp(prompt->full_args[i], ";")))
			get_exec(prompt, i, value, garbage);
		else if (i != 0 && !ft_strcmp(prompt->full_args[i], "|"))
			get_exec_pipe (prompt, i, value, garbage);
	}
	close(prompt->tmp_fd);
}

static int	get_exec(t_prompt *prompt, int i, int value, t_garbage *garbage)
{
	if (!prompt->next_cmd && !prompt->prev_cmd && \
				!ft_strcmp(prompt->cmd, "exit"))
		ft_exit(garbage, prompt->full_args);
	prompt->exec_pid = fork();
	if (prompt->exec_pid == 0)
	{
		if (is_builtin(prompt->full_args[0]))
			exec_builtin(prompt, garbage);
		else if (ft_execute(prompt->full_args, i, prompt->tmp_fd, environ))
			return (1);
	}
	else
	{
		close(prompt->tmp_fd);
		waitpid(prompt->exec_pid, &value, WUNTRACED);
		if (WIFEXITED(value))
			errno = WEXITSTATUS(value);
		prompt->tmp_fd = dup(STDIN_FILENO);
	}
	return (0);
}

static int	get_exec_pipe(t_prompt *prompt, int i, int value, t_garbage *garbage)
{
	pipe(prompt->exec_fd);
	prompt->exec_pid= fork();
	if (prompt->exec_pid == 0)
	{
		dup2(prompt->exec_fd[1], STDOUT_FILENO);
		close(prompt->exec_fd[0]);
		close(prompt->exec_fd[1]);
		if (is_builtin(prompt->full_args[0]))
			exec_builtin(prompt, garbage);
		else if (ft_execute(prompt->full_args, i, prompt->tmp_fd, environ))
			return (1);
	}
	else
	{
		close(prompt->exec_fd[1]);
		close(prompt->tmp_fd);
		waitpid(prompt->exec_pid, &value, WUNTRACED);
		if (WIFEXITED(value))
			errno = WEXITSTATUS(value);
		prompt->tmp_fd = prompt->exec_fd[0];
	}
	return (0);
}

static int	ft_putstr_error(char *str, char *arg)
{
	while (str && *str)
		write(2, str++, 1);
	if (arg)
		while (*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
	return (1);
}

static int	ft_execute(char **args, int i, int tmp_fd, char **envp)
{
	args[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(args[0], args, envp);
	return (ft_putstr_error("error : cannot execute ", args[0]));
}
