/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/04 20:30:32 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern char **environ;


static int get_execute(char **argv, int tmp_fd, char **envp);

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
		prompt->args[0] = "-";
		if (!ft_strcmp(prompt->cmd, "ls"))
			prompt->args[0] = getenv("PWD");
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

void	exec(char *path, t_prompt *prompt, t_garbage *garbage)
{
	int tmp_fd;
	int fd[2];
	char **args = NULL;

	tmp_fd = dup(STDIN_FILENO);
	args = get_exec_args( path, prompt, garbage);
	while(prompt->cmd)
	{
		if (!prompt->next_cmd)
		{
			if (fork() == 0)
			{
				if (get_execute(args, tmp_fd, environ))
					break ;
			}
			else
			{
				close(tmp_fd);
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					;
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if (prompt->next_cmd)
		{
			pipe (fd);
			if (fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if (get_execute(args, tmp_fd, environ))
					return ;
			}
			else
			{
				//while (waitpid(-1, NULL, WUNTRACED) != -1)
				//	;
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
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

static int get_execute(char **args, int tmp_fd, char **envp)
{
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
//	printf("%s", args[0]);
	execve(args[0], args, envp);
	return (ft_putstr_error("error : cannot execute ", args[0]));
}