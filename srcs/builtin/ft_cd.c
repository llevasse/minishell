/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/20 13:56:40 by llevasse         ###   ########.fr       */
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
	replace_env("OLDPWD", new_path);
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
	if (!ft_strncmp(new_path, prompt->full_args[1], ft_strlen(new_path)))
		return ;
//	new_path = ft_strjoin(
//				ft_strjoin(ft_getenv(g_minishell.env, "PWD", garbage),
//					"/"), prompt->args[0]);
// why ? 
	else if (!strncmp(prompt->full_args[1], "~/", 2))
	{
		new_path = ft_joinf("%s/%s", ft_getenv(g_minishell.env,
					"HOME", garbage), &prompt->full_args[1][3]);
		printf("%s\n", prompt->full_args[1]);
	}
	else
		new_path = ft_strjoin("", prompt->args[0]);
	printf("New path : |%s|\n", new_path);
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
		g_minishell.env = insert_alpha(ft_joinf("PWD=%s", new_path),
				g_minishell.env, g_minishell.at_exit_garbage);
	}
	else
		ft_printf("cd Failure\n");
}
