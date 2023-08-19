/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:25:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/19 10:57:38 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**insert_at_end(char *s, char **tab, t_garbage *garbage)
{
	char	**new;
	int		i;

	new = malloc((get_tab_size(tab) + 2) * sizeof(char *));
	ft_add_garbage(0, &garbage, new);
	i = 0;
	while (tab[i])
	{
		new[i] = tab[i];
		new[i++ + 1] = NULL;
	}
	new[i] = s;
	new[i + 1] = NULL;
	return (new);
}

char	**insert_s_at_index(char *s, char **tab, int index, t_garbage *garbage)
{
	char	**new;
	int		i;

	new = malloc((get_tab_size(tab) + 2) * sizeof(char *));
	ft_add_garbage(0, &garbage, new);
	i = 0;
	while (tab[i] && i < index)
	{
		new[i] = tab[i];
		new[i++ + 1] = NULL;
	}
	new[i] = s;
	new[i++ + 1] = NULL;
	while (tab[i])
	{
		new[i] = tab[i - 1];
		new[i++ + 1] = NULL;
	}
	return (new);
}

char	**insert_alpha(char *s, char **tab, t_garbage *garbage)
{
	int			i;

	i = 0;
	if (ft_strcmp(s, tab[1]) < 0)
		return (insert_s_at_index(s, tab, i, garbage));
	while (tab[i] && tab[i + 1])
	{
		if (ft_strcmp(s, tab[i]) > 0 && ft_strcmp(s, tab[i + 1]) < 0)
			return(insert_s_at_index(s, tab, i, garbage));
		i++;
	}
	return (insert_at_end(s, tab, garbage));
}

char	**insert_tab_at_index(char **t1, char **t2,
			int index, t_garbage *garbage)
{
	char	**new;
	int		i;
	int		j;

	new = malloc((get_tab_size(t1) + get_tab_size(t2) + 1) * sizeof(char *));
	ft_add_garbage(0, &garbage, new);
	if (!new)
		return (t1);
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
