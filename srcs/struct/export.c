/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:08 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 01:25:11 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*ft_new_export(char *key, char *content, t_minishell *shell)
{
	t_export	*new;

	new = malloc(sizeof(struct s_export));
	ft_add_garbage(0, &shell->garbage, new, shell);
	new->key = key;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_add_export(t_export **lst, char *key, char *content,
			t_minishell *shell)
{
	t_export	*temp;
	t_export	*new;

	new = ft_new_export(key, content, shell);
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

int	export_list_size(t_export *export)
{
	if (export)
		return (export_list_size(export->next) + 1);
	return (0);
}
