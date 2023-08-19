/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/19 13:17:31 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;


static int	ft_is_cd_args(char *args);
static void	cd_with_args(t_prompt *prompt, char *new_path,
				char cwd[PATH_MAX], t_garbage *garbage);
static void	cd_without_args(char *new_path, t_garbage *garbage);

void	ft_cd(t_prompt *prompt, t_garbage *garbage)
{
	char	*new_path;
	char	cwd[PATH_MAX];

	new_path = get_pwd(garbage);
	sort_tab_alpha(g_minishell.env);
	delete_duplicate_export("OLDPWD");
	g_minishell.env = insert_alpha(ft_joinf("OLDPWD=%s", new_path),
			g_minishell.env, g_minishell.at_exit_garbage);
	if (!ft_is_cd_args(prompt->full_args[1]))
		cd_without_args(new_path, garbage);
	else
		cd_with_args(prompt, new_path, cwd, garbage);
}

static int	ft_is_cd_args(char *args)
{
	if (!ft_strcmp(args, "|") || !ft_strcmp(args, ";") || !args)
		return (0);
	else
		return (1);
}

/// @brief Replace doubles quotes with it's content
/// @param *prompt Pointer prompt struct,
/// @param *new_path Pointer to str,
/// @param *garbage Pointer to garbage struct.
static void	cd_with_args(t_prompt *prompt, char *new_path,
							char cwd[PATH_MAX], t_garbage *garbage)
{
	if (!ft_strncmp(new_path, prompt->args[0], ft_strlen(new_path)))
		new_path = ft_strjoin(
				ft_strjoin(ft_getenv(g_minishell.env, "PWD", garbage),
					"/"), prompt->args[0]);
	else
		new_path = ft_strjoin("", prompt->args[0]);
	if (chdir(new_path) == 0)
	{
		free(new_path);
		getcwd(cwd, PATH_MAX);
	}
	else
	{
		free(new_path);
		ft_printf("wrong directory\n");
	}
}

static void	cd_without_args(char *new_path, t_garbage *garbage)
{
	new_path = ft_getenv(g_minishell.env, "HOME", garbage);
	if (chdir(new_path) == 0)
	{
		sort_tab_alpha(g_minishell.env);
		delete_duplicate_export("PWD");
		g_minishell.env = insert_alpha(ft_joinf("PWD=%s", new_path), g_minishell.env , g_minishell.at_exit_garbage);
	}
	else
		ft_printf("cd Failure\n");
}