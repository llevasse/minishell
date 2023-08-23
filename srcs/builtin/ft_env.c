/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:02 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/23 13:15:27 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

void	replace_env(char *var_name, char *new_value)
{
	int	i;

	i = 0;
	delete_duplicate_export(var_name);
	var_name = ft_strjoin(var_name, "=");
	ft_add_garbage(0, &g_minishell.garbage, var_name);
	new_value = ft_strjoin(var_name, new_value);
	ft_add_garbage(0, &g_minishell.at_exit_garbage, new_value);
	while (g_minishell.env[i])
	{
		if (!ft_strncmp(var_name, g_minishell.env[i], ft_strlen(var_name)))
		{
			g_minishell.env[i] = new_value;
			return ;
		}
		i++;
	}
	g_minishell.env = insert_at_end(new_value,
			g_minishell.env, g_minishell.at_exit_garbage);
}

int	test(int i)
{
	char	**print;
	int		j;

	j = 0;
	print = ft_split(g_minishell.env[i++], '=');
	ft_add_garbage(0, &g_minishell.garbage, print);
	if (print[1])
		printf("%s=", print[j]);
	ft_add_garbage(0, &g_minishell.garbage, print[j++]);
	while (print[j])
	{
		printf("%s", print[j]);
		ft_add_garbage(0, &g_minishell.garbage, print[j++]);
		if (print[j])
			printf("=");
	}
	if (print[1])
		printf("\n");
	return (i);
}

void	ft_env(void)
{
	int		i;

	i = 0;
	while (g_minishell.env[i])
	{
		if (ft_strncmp("_=", g_minishell.env[i], 2))
			i = test(i);
		else
			i++;
	}
	ft_printf("_=/usr/bin/env\n");
}
