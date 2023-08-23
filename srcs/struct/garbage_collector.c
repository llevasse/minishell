/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:05:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/24 00:22:10 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_garbage(t_garbage	*garbage)
{
	if (garbage)
	{
		free_garbage(garbage->next);
		garbage->next = NULL;
		if (garbage->address)
		{
			free(garbage->address);
			garbage->address = NULL;
		}
		free(garbage);
		garbage = NULL;
	}
}

t_garbage	*ft_new_garbage(int log, void *address)
{
	t_garbage	*new;

	new = malloc(sizeof(struct s_garbage));
	if (!new)
		return ((void)(errno = 12), NULL);
	if (log)
		printf(ADD_GARBAGE, address, (char *)address);
	new->address = address;
	new->next = NULL;
	return (new);
}

void	malloc_failed(t_garbage *garbage)
{
	errno = 12;
	free_garbage(garbage);
	garbage = ft_new_garbage(0, NULL);
	minishell_loop(garbage);
	exit(12);
}

void	ft_add_garbage(int log, t_garbage **lst, void *address)
{
	t_garbage	*temp;
	t_garbage	*new;

	if (!address)
		malloc_failed(*lst);
	new = ft_new_garbage(log, address);
	if (!new)
		malloc_failed(*lst);
	if (*lst)
	{
		temp = *lst;
		while (temp->next != NULL)
		{
			if (temp->address == address)
				return (free(new));
			temp = temp->next;
		}
		if (temp->address == address)
			return (free(new));
		temp->next = new;
		return ;
	}
	*lst = new;
}
