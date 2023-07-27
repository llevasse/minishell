/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:23 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/27 12:52:52 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern char	**environ;

static int	unset_env(char *arg, size_t size);

void	ft_unset(t_prompt *prompt)
{
	char	path[PATH_MAX];

	ft_bzero(path, PATH_MAX);
	if (!prompt->args)
		return ;
	if (!ft_strcmp(prompt->args[0], "PWD"))
		setenv("OLDPWD", getcwd(path, PATH_MAX), 1);
	if (prompt->args[0])
		if (!unset_env(prompt->args[0], ft_strlen(prompt->args[0])))
			return ;
}

static int	unset_env(char *arg, size_t size)
{
	ssize_t	i;

	i = -1;
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], arg, size))
		{
			environ[i] = "";
			return (1);
		}
	}
	return (0);
}
