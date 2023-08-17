/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:08 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/17 15:37:02 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

t_export	*ft_new_export(char *key, char *content, t_garbage *garbage)
{
	t_export	*new;

	new = malloc(sizeof(struct s_export));
	ft_add_garbage(0, &garbage, new);
	new->key = key;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_add_export(t_export **lst, char *key, char *content,
			t_garbage *garbage)
{
	t_export	*temp;
	t_export	*new;

	new = ft_new_export(key, content, garbage);
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

char	**convert_to_tab(t_export *export)
{
	char		**tab;
	t_export	*temp;
	int			i;

	tab = malloc(sizeof(char *) * (export_list_size(export) + 1));
	ft_add_garbage(0, &(g_minishell.at_exit_garbage), tab);
	i = 0;
	temp = export;
	while (temp)
	{
		tab[i] = ft_joinf("%s=%s", temp->key, temp->content);
		ft_add_garbage(0, &(g_minishell.at_exit_garbage), tab[i++]);
		temp = temp->next;
	}
	tab[i] = NULL;
	return (tab);
}
