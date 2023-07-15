/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:05:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/15 08:59:51 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_garbage(t_garbage	*garbage)
{
	if (garbage)
	{
	free_garbage(garbage->next);
	free(garbage->address);
	free(garbage);
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
	
	if (!address)
		return (ft_exit(*lst));
	if (*lst)
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = ft_new_garbage(address, *lst);
		return ;
	}
	*lst = ft_new_garbage(address, *lst);
}
