/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 21:22:57 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 01:24:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_tab_alpha_sorted(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && tab[i + 1])
	{
		if (ft_strncmp("_=", tab[i + 1], 2) && \
		ft_strcmp(tab[i], tab[i + 1]) > 0)
			return (0);
		i++;
	}
	return (1);
}

void	sort_tab_alpha(char **tab)
{
	int		i;
	char	*temp;

	while (!is_tab_alpha_sorted(tab))
	{
		i = 0;
		while (tab[i] && tab[i + 1])
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
			}
			i++;
		}
	}
}
