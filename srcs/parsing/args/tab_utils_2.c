/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:22:27 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/22 20:25:59 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_arg	**move_args(t_arg **new, t_arg **t1, t_arg **t2, int index)
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
							int index, t_garbage *garbage)
{
	t_arg	**new;

	new = malloc((get_arg_size(t1) + get_arg_size(t2) + 1) * sizeof(t_arg *));
	ft_add_garbage(0, &garbage, new);
	if (!new)
		return (t1);
	new = move_args(new, t1, t2, index);
	return (new);
}