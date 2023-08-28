/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/28 10:46:09 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_cd_args(char *args);
static void	cd_with_args(t_prompt *prompt, char *new_path,
				char cwd[PATH_MAX]);
static void	cd_without_args(char *new_path, t_minishell *shell);

/// @brief Change current directory.
/// @param *prompt Pointer prompt struct,
/// @param *garbage Pointer to garbage struct.
void	ft_cd(t_prompt *prompt)
{
	char	*new_path;
	char	cwd[PATH_MAX];

	new_path = get_pwd(prompt->shell);
	if (!(prompt->full_args[1]) || !ft_is_cd_args(prompt->full_args[1]->s))
		cd_without_args(new_path, prompt->shell);
	else
		cd_with_args(prompt, new_path, cwd);
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
static void	cd_with_args(t_prompt *prompt, char *new_path, char cwd[PATH_MAX])
{
	if (prompt->args[1])
		write(2, TMA, ft_strlen(TMA));
	if (!ft_strncmp(new_path, prompt->full_args[1]->s, ft_strlen(new_path)))
		return ;
	else if (!ft_strcmp(prompt->full_args[1]->s, "-"))
		new_path = ft_joinf("%s", ft_getenv(prompt->shell->env, \
		"OLDPWD", prompt->shell));
	else if (!ft_strncmp(prompt->full_args[1]->s, "~/", 2))
		new_path = ft_joinf("%s/%s", ft_getenv(prompt->shell->env,
					"HOME", prompt->shell), &prompt->full_args[1]->s[2]);
	else
		new_path = ft_strjoin("", prompt->args[0]->s);
	cwd = ft_getenv(prompt->shell->env, "PWD", prompt->shell);
	if (chdir(new_path) == 0)
	{
		replace_env("OLDPWD", cwd, prompt->shell);
		free(new_path);
		replace_env("PWD", cwd, prompt->shell);
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
static void	cd_without_args(char *new_path, t_minishell *shell)
{
	new_path = ft_getenv(shell->env, "HOME", shell);
	if (!new_path)
	{
		write(2, NO_HOME, ft_strlen(NO_HOME));
		errno = 1;
	}
	else if (chdir(new_path) == 0)
	{
		sort_tab_alpha(shell->env);
		replace_env("PWD", new_path, shell);
	}
	else
		ft_printf("cd Failure\n");
}
