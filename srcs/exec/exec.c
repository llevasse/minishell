/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/07/18 08:54:06 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	false_exec(char *path, t_prompt *prompt)
{
	pid_t	pid;
	char	*argv[3];

	pid = fork();
	if (pid == -1)
		return ((void)write(2, "fork error\n", 11), exit(-1));
	else if (pid == 0)
	{
		if (!prompt->args)
		{
			prompt->args = malloc(sizeof(char *) * 1);
			if (!prompt->args)
				return ((void) write(2, "error\n", 6), exit(-1));
			prompt->args[0] = getenv("PWD");
		}
		argv[0] = ft_strjoin(ft_strjoin(path, "/"), prompt->cmd);
		printf("%s\n", argv[0]);
		argv[1] = prompt->args[0];
		argv[2] = NULL;
		if (access(argv[0], X_OK == -1))
			return ((void) write(2, "Error, no builtin found\n", 26));
		execve(argv[0], argv, environ);
	}
	else
		wait(NULL);
}
