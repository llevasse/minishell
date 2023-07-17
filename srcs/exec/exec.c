/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:49:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/17 11:09:19 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	false_exec(char *path, t_prompt *prompt)
{
	pid_t	pid;

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
			prompt->args[0] = NULL;
		}
		char *argv[] = {ft_strjoin(ft_strjoin(path, "/"), prompt->cmd), prompt->args[0], NULL};
		printf("Coucou, j'exec le programme a %s/%s :O", path, prompt->cmd);
		if (access(argv[0], X_OK == -1))
			return ((void) write(2, "Error, no avaible builtin\n", 26));
		execve(argv[0], argv, NULL);
	}
	else
		wait(NULL);
}
