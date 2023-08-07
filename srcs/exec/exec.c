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

extern char	**environ;

void	false_exec(char *path, t_prompt *prompt, t_garbage *garbage, int tmp_fd);
void	last_exec(char *path, t_prompt *prompt, t_garbage *garbage, int tmp_fd);

//pipe_fd[0] - read
//pipe_fd[1] - write
void	exec(char *path, t_prompt *prompt, t_garbage *garbage)
{
	int	tmp_fd;

	tmp_fd = dup(STDIN_FILENO);
	if (prompt->next_cmd) {
		while (prompt->next_cmd) {
			false_exec(path, prompt, garbage, tmp_fd);
			prompt = prompt->next_cmd;
		}
	}
	else
		last_exec(path, prompt, garbage, tmp_fd);
	close(tmp_fd);
}

void	false_exec(char *path, t_prompt *prompt, t_garbage *garbage, int tmp_fd)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	**argv;


	if (pipe(pipe_fd) == -1)
		return ((void)write(2, "pipe error\n", 11), exit(-1));
	pid = fork();
	if (pid == -1)
		return ((void)write(2, "fork error\n", 11), exit(-1));
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		argv = pass_args_exec(path, prompt, garbage);
		if (access(argv[0], X_OK == -1))
			return ((void) write(2, "Error, no builtin found\n", 25));
		dup2(tmp_fd, STDIN_FILENO);
		execve(argv[0], argv, environ);
	}
	else
	{
		close(pipe_fd[1]);
		close(tmp_fd);
		tmp_fd = pipe_fd[0];
	}
}

//pipe_fd[0] - read
//pipe_fd[1] - write
void	last_exec(char *path, t_prompt*prompt, t_garbage *garbage, int tmp_fd)
{
	pid_t	pid;
	char	**argv;

	pid = fork();
	if (pid == -1)
		return ((void)write(2, "fork error\n", 11), exit(-1));
	if (pid == 0)
	{
		argv = pass_args_exec(path, prompt, garbage);
		if (access(argv[0], X_OK == -1))
			return ((void) write(2, "Error, no builtin found\n", 25));
		execve(argv[0], argv, environ);
	}
	else
	{
		close(tmp_fd);
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
		tmp_fd = dup(STDIN_FILENO);
	}
}


/// @brief Get number of element in **tab.
/// @param **tab Pointer to pointers of char.
/// @return Return number of element in tab.
int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// command like cat or grep passed without argument
// will not work if '-' is not added as argument.
// where command like ls will need PWD.
/// @brief Get arguments to pass to execve.
/// @param *path String of path to executable,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage struct.
/// @return Return arguments to pass in execve.
char	**pass_args_exec(char *path, t_prompt *prompt, t_garbage *garbage)
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
