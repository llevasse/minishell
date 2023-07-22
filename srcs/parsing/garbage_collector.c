/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:05:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/22 22:23:15 by llevasse         ###   ########.fr       */
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
			printf("Attempting to free address %p with content |%s|\n", garbage->address, (char *)garbage->address);
			free(garbage->address);
			garbage->address = NULL;
		}
		free(garbage);
		garbage = NULL;
	}
}

t_garbage	*ft_new_garbage(void	*address, t_garbage *garbage)
{
	t_garbage	*new;

	new = malloc(sizeof(struct s_garbage));
	if (!new)
		return (ft_exit(garbage), NULL);
	new->address = address;
	new->next = NULL;
	return (new);
}

void	ft_add_garbage(t_garbage **lst, void *address)
{
	t_garbage	*temp;
	t_garbage	*new;

	if (!address)
		return (ft_exit(*lst));
	new = ft_new_garbage(address, *lst);
	if (*lst)
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		return ;
	}
	*lst = new;
}
