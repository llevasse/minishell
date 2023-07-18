/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/18 11:39:55 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_new_path(char **directory, char *new_path, size_t i)
{
	while (directory[++i])
	{
		if (!ft_strcmp(directory[i + 1], "."))
		{
			new_path = ft_strjoin(ft_strjoin(new_path, "/"), directory[i]);
			if (!directory[i + 1])
				break ;
			i++;
		}
		else if (!ft_strcmp(directory[i + 1], ".."))
		{
			if (!directory[i + 1])
				break ;
			i += 1;
		}
		else
			new_path = ft_strjoin(ft_strjoin(new_path, "/"), directory[i]);
	}
	return (new_path);
}

char	*ft_clear_path(char *path)
{
	char	*new_path;
	char	**directory;

	directory = ft_split(path, '/');
	free(path);
	new_path = malloc(sizeof(char) * 1);
	if (!new_path)
		return (exit(-1), NULL);
	new_path[0] = '\0';
	new_path = get_new_path(directory, new_path, -1);
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
			setenv("PWD", new_path, 1);
		else
			printf("echec\n");
	}
	else if (prompt->args)
	{
		new_path = ft_strjoin(ft_strjoin(getenv("PWD"), "/"), prompt->args[0]);
		new_path = ft_clear_path(new_path);
		if (chdir(new_path) == 0)
		{
			printf("%s\n", new_path);
			setenv("PWD", new_path, 1);
		}
		else
			ft_printf("wrong directory\n");
	}
}
