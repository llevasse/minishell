/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:20:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/21 23:27:01 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_minishell	g_minishell;

static void	update_shlvl(char **env, t_garbage *garbage)
{
	int		lvl;
	char	*new_lvl;
	int		i;

	lvl = ft_atoi(ft_getenv(env, "SHLVL", garbage));
	lvl++;
	i = 0;
	while (env[i] && ft_strncmp("SHLVL=", env[i], 6))
		i++;
	if (!env[i])
		return ;
	new_lvl = ft_itoa(lvl);
	ft_add_garbage(0, &garbage, new_lvl);
	env[i] = ft_joinf("SHLVL=%s", new_lvl);
	ft_add_garbage(0, &garbage, env[i]);
}

char	**get_base_env(void)
{
	char	**environ;
	char	path[PATH_MAX];

	environ = malloc(sizeof(char *) * 4);
	if (!environ)
		return (NULL);
	environ[0] = ft_joinf("PWD=%s", getcwd(path, PATH_MAX));
	environ[1] = "SHLVL=0";
	environ[2] = "OLDPWD";
	environ[3] = NULL;
	return (environ);
}

void	set_env(char **envp, t_garbage *garbage_at_exit)
{
	if (!envp || !envp[0])
	{
		envp = get_base_env();
		if (!envp || !envp[0])
			exit (errno);
		ft_add_garbage(0, &g_minishell.at_exit_garbage, envp[0]);
	}
	update_shlvl(envp, garbage_at_exit);
	g_minishell.entry_env = envp;
	g_minishell.env = envp;
	g_minishell.at_exit_garbage = garbage_at_exit;
}
