/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/17 19:02:10 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_dir(char *path)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = ft_strlen(path);
	while (path[i] && path[i] != '/')
		i--;
	new = malloc(sizeof(char ) * i + 1);
	if (!new)
		return (exit(-1), NULL);
	j = 0;
	while (path[j] != '/' && j < i)
	{
		new[j] = path[j];
		j++;
	}
	new[j] = '\0';
	printf ("in remove : %s\n", new);
	return (new);
}

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
			printf(".. \n");
			if (directory[i + 1])
				i += 1;
		}
		else
		{
			printf("test %zu: %s\n", i, new_path);
			new_path = ft_strjoin(ft_strjoin(new_path, "/"), directory[i]);
		}
	}
	printf("clear path : %s\n", new_path);
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
			printf("%s\n", new_path);
		}
		else
			printf("echec\n");
	}
	else if (prompt->args)
	{
		new_path = ft_strjoin(ft_strjoin(getenv("PWD"), "/"), prompt->args[0]);
		printf("before: %s\n", new_path);
		new_path = ft_clear_path(new_path);
		if (chdir(new_path) == 0)
		{
			setenv("PWD", new_path, 1);
			printf("in : %s\n", new_path);
		}
		else
			ft_printf("wrong directory\n");
	}
}
