/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/25 14:49:18 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_cd(t_prompt *prompt)
{
	char	*new_path;
	char 	cwd[PATH_MAX];


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
		if (chdir(new_path) == 0)
		{
			getcwd(cwd, PATH_MAX);
			setenv("PWD", cwd, 1);
		}
		else
			ft_printf("wrong directory\n");
	}
}
