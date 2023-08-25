/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:05:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/25 21:48:17 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

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

t_garbage	*ft_new_garbage(void *address)
{
	t_garbage	*new;

	new = malloc(sizeof(struct s_garbage));
	if (!new)
		return ((void)(errno = 12), NULL);
	new->address = address;
	new->next = NULL;
	return (new);
}

void	malloc_failed(int at_exit, t_garbage *garbage)
{
	errno = 12;
	free_garbage(garbage);
	if (!at_exit)
	{
		garbage = ft_new_garbage(NULL);
		minishell_loop(garbage);
	}
	else
	{
		free_garbage(g_minishell.garbage);
	}
	exit(g_minishell.error_value);
}

void	ft_add_garbage(int exit, t_garbage **lst, void *addr, 
	t_minishell *shell)
{
	t_garbage	*temp;
	t_garbage	*new;

	if (!addr)
		malloc_failed(exit, *lst);
	new = ft_new_garbage(addr);
	if (!new)
		malloc_failed(exit, *lst);
	if (*lst)
	{
		temp = *lst;
		while (temp->next != NULL)
		{
			if (temp->addr == addr)
				return (free(new));
			temp = temp->next;
		}
		if (temp->addr == addr)
			return (free(new));
		temp->next = new;
		return ;
	}
	*lst = new;
}
