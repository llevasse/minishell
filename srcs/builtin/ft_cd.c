/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/30 16:50:19 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	cd_with_args(t_prompt *prompt, char *new_path, char cwd[PATH_MAX]);
static void	cd_without_args(char *new_path);

void	ft_cd(t_prompt *prompt)
{
	char	*new_path;
	char	cwd[PATH_MAX];

	new_path = NULL;
	if (!prompt->args)
		cd_without_args(new_path);
	else if (prompt->args)
		cd_with_args(prompt, new_path, cwd);
}


/// @brief Replace doubles quotes with it's content
/// @param *prompt Pointer prompt struct,
/// @param *new_path Pointer to str,
/// @param *garbage Pointer to garbage struct.
static void	cd_with_args(t_prompt *prompt, char *new_path, char cwd[PATH_MAX])
{
	if (!ft_strncmp(new_path, prompt->args[0], ft_strlen(new_path)))
		new_path = ft_strjoin(
				ft_strjoin(getenv("PWD"), "/"), prompt->args[0]);
	else
		new_path = ft_strjoin("", prompt->args[0]);
	if (chdir(new_path) == 0)
	{
		free(new_path);
		getcwd(cwd, PATH_MAX);
		setenv("PWD", cwd, 1);
	}
	else
	{
		if (chdir(prompt->args[0]) == 0)
			setenv("PWD", prompt->args[0], 1);
		else
			printf("Error :(\n");
	}
}

static void	cd_without_args(char *new_path)
{
	char	*user;

	user = getenv("USER");
	if (!ft_strcmp(user, ""))
		ft_printf("HOME not set !");
	new_path = ft_strjoin("/Users/", user);
	if (chdir(new_path) == 0)
	{
		setenv("PWD", new_path, 1);
		free(new_path);
	}
	else
		printf("Failure\n");
}
