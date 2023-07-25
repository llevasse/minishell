/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/25 16:18:23 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_cd(t_prompt *prompt)
{
	char	*new_path;
	char	cwd[PATH_MAX];


	new_path = getenv("PWD");
	if (!prompt->args)
	{
		new_path = ft_strjoin("/Users/", getenv("USER"));
		if (chdir(new_path) == 0)
		{
			setenv("PWD", new_path, 1);
			free(new_path);
		}
		else
			printf("Failure\n");
	}
	else if (prompt->args)
	{
		if ((ft_strncmp(new_path, prompt->args[0], ft_strlen(new_path)) == 0))
			new_path = ft_strjoin(ft_strjoin(getenv("PWD"), "/"), prompt->args[0]);
		else
			new_path = ft_strjoin("", prompt->args[0]);
		printf("%s\n", new_path);
		if (chdir(new_path) == 0)
		{
			free(new_path);
			getcwd(cwd, PATH_MAX);
			setenv("PWD", cwd, 1);
		}
		else
			ft_printf("wrong directory\n");
	}
}
