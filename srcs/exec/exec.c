/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/27 10:57:20 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exec(t_prompt *prompt, int i);
static int	get_exec_pipe(t_prompt *prompt, int i);
static void	pls_wait(t_prompt *prompt);

void	handler_2(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
}

void	exec(t_prompt *prompt)
{
	int					i;
	t_prompt			*temp;

	i = 0;

	temp = prompt;
	while (prompt->full_args && prompt->full_args[i])
	{
		while (prompt->full_args[i] && cmp_exec(prompt, i))
			i++;
		if (i != 0 && (prompt->full_args[i] == NULL || \
				!ft_strcmp(prompt->full_args[i]->s, ";")))
			get_exec(prompt, i);
		else if (i != 0 && !ft_strcmp(prompt->full_args[i]->s, "|"))
			get_exec_pipe (prompt, i);
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
	do_close(&prompt->tmp_fd);
}

static int	get_exec(t_prompt *prompt, int i)
{

	//TODO: delete this
	struct sigaction sigint_parent;
	struct sigaction sigint_child;

	sigint_parent.sa_flags = SA_RESTART;
	sigint_parent.sa_handler = SIG_IGN;
	sigemptyset(&sigint_parent.sa_mask);
	sigint_child.sa_flags = SA_RESTART;
	sigint_child.sa_handler = SIG_DFL;
	sigemptyset(&sigint_child.sa_mask);
	//END DELETE THIS
	if (!redir(prompt) || !prompt->cmd)
		return ((void)(prompt->has_exec = 1), 1);
	if (!prompt->prev_cmd && !ft_strcmp(prompt->cmd, "exit"))
		ft_exit(prompt->shell, prompt->args);
	if (exec_builtin_main_thread(prompt))
		return (0);
	prompt->exec_pid = fork();
	if (prompt->exec_pid == 0)
	{
		sigaction(SIGINT, &sigint_child, NULL);
		reset_termios();
		if (prompt->prev_cmd)
			prompt->tmp_fd = dup(prompt->exec_fd[0]);
		if (is_builtin(prompt->full_args[0]->s))
			exec_builtin(prompt);
		return (ft_execute(prompt->full_args, i, prompt->tmp_fd, \
				prompt->shell));
	}
	else
	{
		sigaction(SIGINT, &sigint_parent, NULL);
		if (prompt->exec_fd[0] != -1)
			do_close(&prompt->exec_fd[0]);
		do_close(&prompt->tmp_fd);
		prompt->has_exec = 1;
	}
	return (0);
}

static int	get_exec_pipe(t_prompt *prompt, int i)
{
	exec_builtin_main_thread(prompt);
	if (pipe(prompt->exec_fd) == -1)
	{
		free_garbage(prompt->garbage);
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
		do_close(&prompt->exec_fd[1]);
		do_close(&prompt->exec_fd[0]);
		reset_termios();
		if (!exec_child(prompt, i))
			return (1);
	}
	else
		prompt->has_exec = 1;
	return (0);
}

int	ft_execute(t_arg **args, int i, int tmp_fd, t_minishell *shell)
{
	char	**c_args;

	if (args[i])
		args[i]->s = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	do_close(&tmp_fd);
	c_args = to_char_array(args, i, shell);
	execve(c_args[0], c_args, shell->env);
	ft_putstr_fd("error : cannot execute ", 2);
	ft_putendl_fd(c_args[0], 2);
	return (1);
}
