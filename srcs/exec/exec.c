/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/22 21:10:41 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static int	get_exec(t_prompt *prompt, int i, int value, t_garbage *garbage);
static int	get_exec_pipe(t_prompt *prompt, int i, int value,
				t_garbage *garbage);
static int	ft_putstr_error(char *str, char *arg);
static int	ft_execute(t_arg **args, int i, int tmp_fd, char **envp, t_prompt *p);

void	exec(t_prompt *prompt, t_garbage *garbage)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	prompt->tmp_fd = dup(STDIN_FILENO);
	while (prompt->full_args[i])
	{
	//	print_prompt(*prompt);
		while (prompt->full_args[i] && \
				ft_strcmp(prompt->full_args[i]->s, ";") && \
					ft_strcmp(prompt->full_args[i]->s, "|"))
			i++;
		if (i != 0 && (prompt->full_args[i] == NULL || \
				!ft_strcmp(prompt->full_args[i]->s, ";")))
			get_exec(prompt, i, value, garbage);
		else if (i != 0 && !ft_strcmp(prompt->full_args[i]->s, "|"))
			get_exec_pipe (prompt, i, value, garbage);
		if (prompt->has_exec && prompt->next_cmd)
		{
			prompt->next_cmd->tmp_fd = prompt->tmp_fd;
			prompt->next_cmd->old_stdout = prompt->old_stdout;
			prompt->next_cmd->old_stdin = prompt->old_stdin;
			prompt->next_cmd->exec_fd[0] = prompt->exec_fd[0];
			prompt->next_cmd->exec_fd[1] = prompt->exec_fd[1];
			prompt = prompt->next_cmd;
			i = 0;
		}
	}
	close(prompt->tmp_fd);
	prompt->exec_fd[0] = -1;
}

static int	get_exec(t_prompt *prompt, int i, int value, t_garbage *garbage)
{
	check_redirection(prompt, garbage);
	delete_redirection(prompt->full_args);
	if (!prompt->next_cmd && !prompt->prev_cmd && \
				!ft_strcmp(prompt->cmd, "exit"))
		ft_exit(garbage, prompt->full_args);
	if (exec_builtin_main_thread(prompt, garbage))
		return (0);
	prompt->exec_pid = fork();
	if (prompt->exec_pid == 0)
	{
		if (is_builtin(prompt->full_args[0]->s))
			exec_builtin(prompt, garbage);
		else if (ft_execute(prompt->full_args, i, prompt->tmp_fd,
				prompt->environ, prompt))
			return (1);
	}
	else
	{
		close(prompt->tmp_fd);
		waitpid(prompt->exec_pid, &value, WUNTRACED);
		if (WIFEXITED(value))
			errno = WEXITSTATUS(value);
		prompt->tmp_fd = dup(STDIN_FILENO);
		prompt->has_exec = 1;
	}
	return (0);
}

static int	get_exec_pipe(t_prompt *prompt, int i, int value,
			t_garbage *garbage)
{
	exec_builtin_main_thread(prompt, garbage);
	pipe(prompt->exec_fd);
	check_redirection(prompt, garbage);
	delete_redirection(prompt->full_args);
	if (prompt->has_redir == 1)
		i = get_arg_size(prompt->args) + 1;
	prompt->exec_pid = fork();
	if (prompt->exec_pid == 0)
	{
		dup2(prompt->exec_fd[1], STDOUT_FILENO);
		dup2(prompt->exec_fd[0], prompt->tmp_fd);
		close(prompt->exec_fd[1]);
		close(prompt->exec_fd[0]);
		if (is_builtin(prompt->full_args[0]->s))
			exec_builtin(prompt, garbage);
		else if (ft_execute(prompt->full_args, i, prompt->tmp_fd,
				prompt->environ, prompt))
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
		prompt->has_exec = 1;
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

static int	ft_execute(t_arg **args, int i, int tmp_fd, char **envp, t_prompt *p)
{
	char	**c_args;
	(void)p;
	if (args[i])
		args[i]->s = NULL;
	write(1,"\0",1); //don't know why but that save the case "cat < test | wc"
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	c_args = to_char_array(args, i, g_minishell.garbage);
	execve(c_args[0], c_args, envp);
	return (ft_putstr_error("error : cannot execute ", c_args[0]));
}
