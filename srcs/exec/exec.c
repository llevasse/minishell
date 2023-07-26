/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/07/26 21:31:08 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern char	**environ;

void	false_exec(char *path, t_prompt *prompt, t_garbage *garbage)
{
	pid_t	pid;
	char	**argv;

	pid = fork();
	if (pid == -1)
		return ((void)write(2, "fork error\n", 11), exit(-1));
	else if (pid == 0)
	{	
		argv = pass_args_exec(path, prompt, garbage);
		if (access(argv[0], X_OK == -1))
			return ((void) write(2, "Error, no builtin found\n", 25));
		execve(argv[0], argv, environ);
	}
	else
		waitpid(pid, NULL, 0);
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
//		printf("Args : |%s|\n", argv[i + 1]);
		i++;
	}
	argv[i + 1] = NULL;
	return (argv);
}
