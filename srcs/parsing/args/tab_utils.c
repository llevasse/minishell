/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:25:39 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/25 22:43:15 by llevasse         ###   ########.fr       */
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

void	delete_arg_at_index(t_arg **tab, int index)
{
	while (tab[index])
	{
		tab[index] = tab[index + 1];
		index++;
	}
}

char	**insert_at_end(char *s, char **tab, t_minishell *shell)
{
	char	**new;
	int		i;

	new = malloc((get_tab_size(tab) + 2) * sizeof(char *));
	if (!new)
		return (tab);
	ft_add_garbage(0, &shell->at_exit_garbage, new, shell);
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

char	**insert_s_at_index(char *s, char **tab, int index, t_minishell *shell)
{
	char	**new;
	int		i;

	new = malloc((get_tab_size(tab) + 2) * sizeof(char *));
	ft_add_garbage(1, &shell->garbage, new, shell);
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

char	**insert_alpha(char *s, char **tab, t_minishell *shell)
{
	int			i;

	i = 0;
	if (ft_strcmp(s, tab[1]) < 0)
		return (insert_s_at_index(s, tab, i, shell));
	while (tab[i] && tab[i + 1])
	{
		if (ft_strcmp(s, tab[i]) > 0 && ft_strcmp(s, tab[i + 1]) < 0)
			return (insert_s_at_index(s, tab, i, shell));
		i++;
	}
	return (insert_s_at_index(s, tab, i + 1, shell));
}
