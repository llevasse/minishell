/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/15 18:19:02 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

static char	*get_current_dir(char **environ);
static int	ft_is_cd_args(char *args);
static void	cd_with_args(t_prompt *prompt, char *new_path, char cwd[PATH_MAX]);
static void	cd_without_args(char *new_path);

void	ft_cd(t_prompt *prompt)
{
	char	*new_path;
	char	cwd[PATH_MAX];
	int		i;

	new_path = get_current_dir(prompt->environ);
	i = -1;
	while (g_minishell.env[++i])
	{
		if (!ft_strncmp(g_minishell.env[i], "PWD=", 4))
			delete_duplicate_export("PWD");
	}
	insert_at_end(ft_joinf("%s%s", "PWD=", new_path),g_minishell.env,
				  g_minishell.at_exit_garbage);
	if (!ft_is_cd_args(prompt->full_args[1]))
		cd_without_args(new_path);
	else
		cd_with_args(prompt, new_path, cwd);
}

static char	*get_current_dir(char **environ)
{
	int	i;

	i = -1;
	while (environ[++i] && ft_strncmp(environ[i], "PWD=", 4))
		;
	return (&environ[i][4]);
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
		free(new_path);
		ft_printf("wrong directory\n");
	}
}

static void	cd_without_args(char *new_path)
{
	new_path = ft_strjoin("/Users/", getenv("USER"));
	if (chdir(new_path) == 0)
	{
		setenv("PWD", new_path, 1);
		free(new_path);
	}
	else
		ft_printf("cd Failure\n");
}
