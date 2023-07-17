/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/17 19:06:41 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_clear_path(char *path)
{
	size_t	i;
	char	*new_path;
	char	**directory;

	i = -1;
	directory = ft_split(path, '/');
	free(path);
	new_path = malloc(sizeof(char) * 1);
	if (!new_path)
		return (exit(-1), NULL);
	new_path[0] = '\0';
	while (directory[++i])
	{
		if (!ft_strcmp(directory[i + 1], "."))
		{
			new_path = ft_strjoin(ft_strjoin(new_path, "/"), directory[i]);
			i++;
		}
		else if (!ft_strcmp(directory[i + 1], ".."))
		{
			if (directory[i + 1])
				i += 1;
		}
		else
			new_path = ft_strjoin(ft_strjoin(new_path, "/"), directory[i]);
	}
	return (new_path);
}

void	ft_cd(t_prompt *prompt)
{
	char	*new_path;

	new_path = getenv("PWD");
	if (!prompt->args)
	{
		new_path = ft_strjoin("/Users/", getenv("USER"));
		if (chdir(new_path) == 0)
		{
			setenv("PWD", new_path, 1);
		}
		else
			printf("echec\n");
	}
	else if (prompt->args)
	{
		new_path = ft_strjoin(ft_strjoin(getenv("PWD"), "/"), prompt->args[0]);
		new_path = ft_clear_path(new_path);
		if (chdir(new_path) == 0)
		{
			setenv("PWD", new_path, 1);
		}
		else
			ft_printf("wrong directory\n");
	}
}
