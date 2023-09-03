/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:31:14 by mwubneh           #+#    #+#             */
/*   Updated: 2023/09/03 15:48:01 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_arg	**move_index(t_arg **new, t_arg **t1, t_arg **t2, int index)
{
	int	i;
	int	j;

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

t_arg	**insert_tab_at_index(t_arg **t1, t_arg **t2,
					int index, t_minishell *shell)
{
	t_arg	**new;

	new = malloc((get_arg_size(t1) + get_arg_size(t2) + 1) * sizeof(t_arg *));
	ft_add_garbage(0, &shell->garbage, new, shell);
	if (!new)
		return (t1);
	new = move_index(new, t1, t2, index);
	return (new);
}

void	add_split_to_garbage(char **str, t_minishell *shell)
{
	int	i;

	i = 0;
	ft_add_garbage(0, &shell->garbage, str, shell);
	while (str[i])
		ft_add_garbage(0, &shell->garbage, str[i++], shell);
}
