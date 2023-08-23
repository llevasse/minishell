/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/23 22:29:40 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

static int	ft_is_cd_args(char *args);
static void	cd_with_args(t_prompt *prompt, char *new_path,
				char cwd[PATH_MAX], t_garbage *garbage);
static void	cd_without_args(char *new_path, t_garbage *garbage);

/// @brief Change current directory.
/// @param *prompt Pointer prompt struct,
/// @param *garbage Pointer to garbage struct.
void	ft_cd(t_prompt *prompt, t_garbage *garbage)
{
	char	*new_path;
	char	cwd[PATH_MAX];

	new_path = get_pwd(garbage);
	replace_env("OLDPWD", new_path);
	if (!ft_is_cd_args(prompt->full_args[1]->s))
		cd_without_args(new_path, garbage);
	else
		cd_with_args(prompt, new_path, cwd, garbage);
}

/// @brief Check if *args is considered a cd valid argument.
/// @param *args string to check.
/// @return Return 1 if *args is a valid argument, return 0 otherwise.
static int	ft_is_cd_args(char *args)
{
	if (!ft_strcmp(args, "|") || !ft_strcmp(args, ";") || !args)
		return (0);
	else
		return (1);
}

/// @brief Change directory to what was passed as args
/// @param *prompt Pointer prompt struct,
/// @param *new_path Current path,
/// @param cwd[PATH_MAX] idk. TODO
/// @param *garbage Pointer to garbage struct.
static void	cd_with_args(t_prompt *prompt, char *new_path,
							char cwd[PATH_MAX], t_garbage *garbage)
{
	if (prompt->args[1])
		write(2, TMA, ft_strlen(TMA));
	if (!ft_strncmp(new_path, prompt->full_args[1]->s, ft_strlen(new_path)))
		return ;
	else if (!ft_strncmp(prompt->full_args[1]->s, "~/", 2))
	{
		new_path = ft_joinf("%s/%s", ft_getenv(g_minishell.env,
					"HOME", garbage), &prompt->full_args[1]->s[3]);
		printf("%s\n", prompt->full_args[1]->s);
	}
	else
		new_path = ft_strjoin("", prompt->args[0]->s);
	if (chdir(new_path) == 0)
	{
		free(new_path);
		getcwd(cwd, PATH_MAX);
	}
	else
	{
		free(new_path);
		write(2, NO_FILE_E, ft_strlen(NO_FILE_E));
	}
}

/// @brief Change directory to HOME env variable.
/// @param *new_path Current path,
/// @param *garbage Pointer to garbage struct.
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
