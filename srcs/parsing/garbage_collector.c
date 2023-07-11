/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:05:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/11 19:18:39 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_garbage(t_garbage	*garbage)
{
	if (!garbage)
		return ;
	free_garbage(garbage->next);
	free(garbage->content);
	free(garbage);
}

t_garbage	ft_new_garbage(void	*address)
{
	t_garbage	*new;

	new = malloc(sizeof(struct s_garbage));
	if (!new)
		return (NULL);
	new->address = address;
	new->next = NULL;
}

void	ft_add_garbage(t_garbage **lst, t_garbage *new)
{
	t_garbage	*temp;

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
