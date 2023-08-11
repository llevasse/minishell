/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/11 19:51:22 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern char **environ;


static int get_execute(char **argv, char **envp);

int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab )
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	**get_exec_args(char *path, t_prompt *prompt, t_garbage *garbage)
{
	char	**argv;
	char	*cmd_path;
	int		i;

	if (!prompt->args)
	{
		prompt->args = malloc(sizeof(char *) * 2);
		ft_add_garbage(0, &garbage, prompt->args);
		prompt->args[1] = NULL;
	}
	argv = malloc(sizeof(char *) * (get_tab_size(prompt->args) + 2));
	ft_add_garbage(0, &garbage, argv);
	cmd_path = ft_strjoin(path, "/");
	ft_add_garbage(0, &garbage, cmd_path);
	argv[0] = ft_strjoin(cmd_path, prompt->cmd);
	ft_add_garbage(0, &garbage, argv[0]);
	i = 0;
	while (prompt->args[i])
	{
		argv[i + 1] = prompt->args[i];
		i++;
	}
	argv[i + 1] = NULL;
	return (argv);
}

void	exec(t_prompt *prompt, t_garbage *garbage)
{
	char **args = NULL;
	while(prompt->cmd)
	{
		args = get_exec_args(prompt, garbage);
		if (!prompt->next_cmd)
		{
			if (fork() == 0)
			{
				reset_stdio_fd(prompt);
				if (get_execute(args, environ))
					break ;
			}
			else
			{
				reset_stdio_fd(prompt);
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					;
			}
		}
		else if (prompt->next_cmd)
		{
			//pipe_fd[0] - read
			//pipe_fd[1] - write
			if (fork() == 0)
			{
				dup2(prompt->heredoc_fd[1], STDOUT_FILENO);
				if (get_execute(args, environ))
					break ;
			}
			else
			{
				dup2(prompt->heredoc_fd[1], STDOUT_FILENO);
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					;
				close(prompt->heredoc_fd[1]);
				dup2(prompt->heredoc_fd[0], prompt->next_cmd->heredoc_fd[1]);
				dup2(prompt->next_cmd->heredoc_fd[1], STDIN_FILENO);
			}
		}
		if (prompt->next_cmd)
			prompt = prompt->next_cmd;
		else
			break ;
	}
}

static int ft_putstr_error(char *str, char *arg)
{
	while (str && *str)
		write(2, str++, 1);
	if (arg)
		while (*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
	return (1);
}

static int get_execute(char **args, char **envp)
{
	execve(args[0], args, envp);
	return (ft_putstr_error("error : cannot execute ", args[0]));
}
