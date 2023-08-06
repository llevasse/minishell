/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:25:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/03 19:24:49 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

///	@brief Delete element in tab at index.
/// @param **tab Pointer to tab,
/// @param index Index of element to delete
void	delete_element_at_index(char **tab, int index)
{
	while (tab[index])
	{
		tab[index] = tab[index + 1];
		index++;
	}
}

char	**insert_tab_at_index(char **t1, char **t2,
			int index, t_garbage *garbage)
{
	char	**new;
	int		i;
	int		j;

	new = malloc((get_tab_size(t1) + get_tab_size(t2) + 1) * sizeof(char *));
	ft_add_garbage(0, &garbage, new);
	i = 0;
	j = 0;
	while (t1[i] && i < index)
	{
		new[i + j] = t1[i];
		new[i++ + j + 1] = NULL;
	}
	while (t2[j])
	{
		new[i + j] = t2[j];
		new[i + j++ + 1] = NULL;
	}
	while (t1[i])
	{
		new[i + j] = t1[i];
		new[i++ + j + 1] = NULL;
	}
	return (new);
}
