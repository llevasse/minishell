/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/17 16:48:28 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *clear_path(char *path)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (exit(-1), NULL);
	j = -1;
	while (++j < i && path[j])
		new[j] = path[j];
	return (new);
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
		if ()
		if (chdir(new_path) == 0)
		{
			setenv("PWD", new_path, 1);
			printf("%s\n", new_path);
		}
		printf("%s\n", prompt->args[0]);
	}
}
