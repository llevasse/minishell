/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/19 13:26:00 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

void	export_listing(char **env, int i);

void	print_export(char **env)
{
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		if (ft_strncmp("_=", env[i], 2))
		{
			export_listing(env, i);
		}
		else
			i++;
	}
}

void	export_listing(char **env, int i)
{
	int		j;
	char	**print;

	j = 0;
	print = ft_split(env[i++], '=');
	ft_add_garbage(0, &g_minishell.garbage, print);
	if (!print[j + 1])
		printf("declare -x %s", print[j]);
	else
		printf("declare -x %s=\"", print[j]);
	ft_add_garbage(0, &g_minishell.garbage, print[j++]);
	while (print[j])
	{
		printf("%s", print[j]);
		ft_add_garbage(0, &g_minishell.garbage, print[j++]);
		if (print[j])
			printf("=");
	}
	if (j > 1)
		printf("\"");
	printf("\n");
}

void	delete_duplicate_export(char *key)
{
	int	i;

	i = 0;
	while (g_minishell.env[i] && \
	ft_strncmp(key, g_minishell.env[i], ft_strlen(key)))
		i++;
	if (g_minishell.env[i])
		delete_element_at_index(g_minishell.env, i);
}

void	ft_export(t_prompt *prompt)
{
	char		*exports;
	t_export	*exp;

	sort_tab_alpha(g_minishell.env);
	if (prompt->export_args)
	{
		exp = prompt->export_args;
		if (!ft_strncmp(exp->key, "_=", 2))
			return ;
		exports = ft_joinf("%s=%s", exp->key, exp->content);
		ft_add_garbage(0, &g_minishell.at_exit_garbage, exports);
		delete_duplicate_export(exp->key);
		g_minishell.env = insert_alpha(exports,
				g_minishell.env, g_minishell.at_exit_garbage);
	}
	else
		print_export(g_minishell.env);
}
