/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:22:57 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/18 21:35:43 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

int	is_tab_alpha_sorted(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && tab[i + 1])
	{
		printf("Comparing %s and %s\n", tab[i], tab[i + 1]);
		if (ft_strncmp("_=", tab[i + 1], 2) && ft_strcmp(tab[i], tab[i + 1]) > 0)
			return (printf("difference of %d :(\n",ft_strcmp(tab[i], tab[i + 1])));
		printf("%s and %s are alright\n", tab[i], tab[i + 1]);
		i++;
	}
	return (0);
}

void	sort_tab_alpha(char **tab)
{
	is_tab_alpha_sorted(tab);
}
