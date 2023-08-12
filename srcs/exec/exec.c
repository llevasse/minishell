/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/11 21:51:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern char	**environ;
extern t_minishell *g_minishell;

static int ft_putstr_error(char *str, char *arg);
static int ft_execute(char **args, int i, int tmp_fd, char **envp);
//static char	**get_exec_args(char *path, t_prompt *prompt, t_garbage *garbage);

void	exec(char *path, t_prompt *prompt, t_garbage *garbage)
{
	int i;
	int fd[2];
	int tmp_fd;
	(void)path;
	(void)garbage;

	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (prompt->full_args[i] && prompt->full_args[i + 1])
	{
		prompt->full_args = &prompt->full_args[i + 1];
		i = 0;
		while (prompt->full_args[i] && ft_strcmp(prompt->full_args[i], ";") && ft_strcmp(prompt->full_args[i], "|"))
			i++;
		if (ft_strcmp(prompt->full_args[0], "cd") == 0) {
			if (i != 2)
				ft_putstr_error("error : cd : bad arguments", NULL);
			else if (chdir(prompt->full_args[1]) != 0)
				ft_putstr_error("error : cd : cannot change directory to ", prompt->full_args[1]);
		} else if (i != 0 && (prompt->full_args[i] == NULL || !ft_strcmp(prompt->full_args[i], ";"))) {
			if (fork() == 0) {
				if (ft_execute(prompt->full_args, i, tmp_fd, prompt->full_args))
					return;
			} else {
				close(tmp_fd);
				while (waitpid(-1, NULL, WUNTRACED) != -1);
				tmp_fd = dup(STDIN_FILENO);
			}
		} else if (i != 0 && !ft_strcmp(prompt->full_args[i], "|")) {
			pipe(fd);
			if (fork() == 0) {
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if (ft_execute(prompt->full_args, i, tmp_fd, environ))
					return ;
			} else {
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	return;
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

static int ft_execute(char **args, int i, int tmp_fd, char **envp)
{
	args[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(args[0], args, envp);
	return (ft_putstr_error("error : cannot execute ", args[0]));
}

int	get_tab_size(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}

//static char	**get_exec_args(char *path, t_prompt *prompt, t_garbage *garbage)
//{
//	char	**argv;
//	char	*cmd_path;
//	int		i;
//
//	if (!prompt->args)
//	{
//		prompt->args = malloc(sizeof(char *) * 2);
//		ft_add_garbage(0, &garbage, prompt->args);
//		prompt->args[0] = NULL;
//		if (!ft_strcmp(prompt->cmd, "ls"))
//			prompt->args[0] = getenv("PWD");
//		prompt->args[1] = NULL;
//	}
//	argv = malloc(sizeof(char *) * (get_tab_size(prompt->args) + 2));
//	ft_add_garbage(0, &garbage, argv);
//	cmd_path = ft_strjoin(path, "/");
//	ft_add_garbage(0, &garbage, cmd_path);
//	argv[0] = ft_strjoin(cmd_path, prompt->cmd);
//	ft_add_garbage(0, &garbage, argv[0]);
//	i = 0;
//	while (prompt->args[i])
//	{
//		argv[i + 1] = prompt->args[i];
//		i++;
//	}
//	argv[i + 1] = NULL;
//	return (argv);
//}
