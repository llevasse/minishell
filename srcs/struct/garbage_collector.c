/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:05:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 01:24:54 by llevasse         ###   ########.fr       */
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

void	malloc_failed(int at_exit, t_minishell *shell)
{
	errno = 12;
	free_garbage(shell->garbage);
	if (!at_exit)
		minishell_loop(shell, ft_new_garbage(NULL));
	else
		free_garbage(shell->at_exit_garbage);
	exit(shell->error_value);
}

void	ft_add_garbage(int exit, t_garbage **lst, void *addr, 
	t_minishell *shell)
{
	t_garbage	*temp;
	t_garbage	*new;

	if (!addr)
		malloc_failed(exit, shell);
	new = ft_new_garbage(addr);
	if (!new)
		malloc_failed(exit, shell);
	if (*lst)
	{
		temp = *lst;
		while (temp->next != NULL)
		{
			if (temp->address == addr)
				return (free(new));
			temp = temp->next;
		}
		if (temp->address == addr)
			return (free(new));
		temp->next = new;
		return ;
	}
	*lst = new;
}
