/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:02 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/19 13:32:59 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

void	ft_env(void)
{
	char	**print;
	int		i;
	int		j;

	i = 0;
	while (g_minishell.env[i])
	{
		if (ft_strncmp("_=", g_minishell.env[i], 2))
		{
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
		}
		else
			i++;
	}
	ft_printf("_=/usr/bin/env\n");
}
