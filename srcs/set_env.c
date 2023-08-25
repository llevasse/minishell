/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:20:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/26 01:29:00 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(char **env, t_minishell *shell)
{
	int		lvl;
	char	*new_lvl;
	int		i;

	lvl = ft_atoi(ft_getenv(env, "SHLVL", shell));
	lvl++;
	i = 0;
	while (env[i] && ft_strncmp("SHLVL=", env[i], 6))
		i++;
	if (!env[i])
		return ;
	new_lvl = ft_itoa(lvl);
	if (!new_lvl)
		return ;
	ft_add_garbage(1, &shell->at_exit_garbage, new_lvl, shell);
	new_lvl = ft_joinf("SHLVL=%s", new_lvl);
	if (!new_lvl)
		return ;
	env[i] = new_lvl;
	ft_add_garbage(1, &shell->at_exit_garbage, env[i], shell);
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

void	set_env(char **envp, t_garbage *garbage, t_minishell *shell)
{
	if (!envp || !envp[0])
	{
		envp = get_base_env();
		ft_add_garbage(1, &garbage, envp, shell);
		if (!envp || !envp[0])
			exit (errno);
		ft_add_garbage(1, &garbage, envp[0], shell);
	}
	update_shlvl(envp, shell);
	shell->entry_env = envp;
	shell->env = envp;
	shell->at_exit_garbage = garbage;
}
