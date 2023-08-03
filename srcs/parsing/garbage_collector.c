/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:05:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/30 16:42:21 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_garbage(t_garbage	*garbage)
{
	if (garbage)
	{
		free_garbage(garbage->next);
		garbage->next = NULL;
		if (garbage->address)
		{
//			printf("Freeing %p with content %s to garbage\n", garbage->address, 				(char *)garbage->address);
			free(garbage->address);
			garbage->address = NULL;
		}
		free(garbage);
		garbage = NULL;
	}
}

t_garbage	*ft_new_garbage(int log, void *address, t_garbage *garbage)
{
	t_garbage	*new;

	new = malloc(sizeof(struct s_garbage));
	if (!new)
		return (ft_exit(garbage), NULL);
	if (log)
		printf("Adding %p with content %s to garbage\n", address, 
			(char *)address);
	new->address = address;
	new->next = NULL;
	return (new);
}

void	ft_add_garbage(int log, t_garbage **lst, void *address)
{
	t_garbage	*temp;
	t_garbage	*new;

	if (!address)
		return (ft_exit(*lst));
	new = ft_new_garbage(log, address, *lst);
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
