/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:49:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/10 00:26:11 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	false_exec(char *path, t_prompt *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ((void)write(2, "fork error\n", 11), exit(-1));
	else if (pid == 0)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof(char *) * 1);
			if (!cmd->args)
				return ((void) write(2, "error\n", 6), exit(-1));
			cmd->args[0] = NULL;
		}
		char *argv[] = {ft_strjoin(ft_strjoin(path, "/"), cmd->cmd), cmd->args[0], NULL};
		if (access(argv[0], X_OK == -1))
			return ((void) write(2, "Error, no avaible builtin\n", 26));
		execve(argv[0], argv, NULL);
	}
	else
		wait(NULL);
}
