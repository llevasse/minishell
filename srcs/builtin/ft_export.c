/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/17 20:55:24 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

void	print_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		printf("%s\n", env[i++]);
}

char	**merge_tabs(char **tab1, char **tab2)
{
	int			nb;
	int			i;
	char		**new;

	nb = get_tab_size(tab1) + get_tab_size(tab2) + 1;
	new = malloc(nb * sizeof(char *));
	ft_add_garbage(0, &g_minishell.at_exit_garbage, new);
	i = 0;
	nb = 0;
	while (tab1[i])
		new[nb++] = tab1[i++];
	i = 0;
	while (tab2[i])
		new[nb++] = tab2[i++];
	return (new[nb] = NULL, new);
}

void	delete_duplicate_export(char *key)
{
	int	i;

	i = 0;
	while (g_minishell.env[i] && ft_strncmp(key, g_minishell.env[i], ft_strlen(key)))
		i++;
	if (g_minishell.env[i])
		delete_element_at_index(g_minishell.env, i);
}

void	ft_export(t_prompt *prompt)
{
	char		*exports;
	t_export	*exp;
	int			i;

	i = 0;
	if (prompt->export_args)
	{
		exp = prompt->export_args;
		exports = ft_joinf("%s=%s", exp->key, exp->content);
		delete_duplicate_export(exp->key);
		g_minishell.env = insert_at_end(exports, g_minishell.env, g_minishell.at_exit_garbage);
	}
	else
		print_env(g_minishell.env);
}

