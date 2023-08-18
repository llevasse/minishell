/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/18 12:43:23 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

void	print_export(char **env)
{
	int		i;
	int		j;
	char	**print;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		while (!ft_strncmp("_=", env[i], 2))
			i++;
		if (!env[i])
			break ;
		j = 0;
		print = ft_split(env[i++], '=');
		ft_add_garbage(0, &g_minishell.garbage, print);
		if (!print[j + 1])
			printf("declare -x %s",print[j]);
		else
			printf("declare -x %s=\"",print[j]);
		ft_add_garbage(0, &g_minishell.garbage, print[j++]);
		while(print[j])
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
		ft_add_garbage(0, &g_minishell.at_exit_garbage, exports);
		delete_duplicate_export(exp->key);
		g_minishell.env = insert_alpha(exports, g_minishell.env , g_minishell.at_exit_garbage);
	}
	else
		print_export(g_minishell.env);
}
