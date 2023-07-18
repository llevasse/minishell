/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:08 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/18 22:01:13 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*ft_new_export(char *key, char *content, t_garbage *garbage)
{
	t_export	*new;

	new = malloc(sizeof(struct s_export));
	ft_add_garbage(&garbage, new);
	new->key = key;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_add_export(t_export **lst, char *key, char *content, t_garbage *garbage)
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

void	get_export_args(t_prompt *prompt, char *input, t_garbage *garbage)
{
	int		equal_pos;
	char	*key;
	char	*content;

	equal_pos = get_char_pos(input, '=');
	if (equal_pos == 0 || ft_isspace(input[equal_pos - 1]))
		return ((void)printf("Bad assignment\n"));
	key = ft_strdup(ft_strsep(&input, "="));
	ft_add_garbage(&garbage, key);
	if (get_char_pos(key, '"') != -1)
		check_quotes(prompt, &key, garbage);
	else
		check_is_env_var(&key, garbage);
	content = ft_strdup(ft_strsep(&input, " "));
	ft_add_garbage(&garbage, content);
	check_quotes(prompt, &content, garbage);
	prompt->export_args = ft_new_export(key, content, garbage);
}
