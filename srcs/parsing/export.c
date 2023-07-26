/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:08 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/26 21:30:28 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

/// @brief get element before '=' when export is called.
/// @param *prompt pointer to prompt struct,
/// @param *input address of string of the prompt input,
/// @param *garbage pointer to garbage collector.
/// @return return string containing key of export.
char	*get_key(t_prompt *prompt, char **input, t_garbage *garbage)
{
	char	*key;	

	key = ft_strdup(ft_strsep(input, "="));
	ft_add_garbage(0, &garbage, key);
	if (get_char_pos(key, '"') != -1 || get_char_pos(key, 39) != -1)
		check_quotes(prompt, &key, garbage);
	else
		check_is_env_var(&key, garbage);
	if (key[0] == '\0')
		return ((void)printf("Bad assignment\n"), NULL);
	if (get_char_pos(key, '$') != -1)
		return ((void)printf("Invalid key : %s\n", key), NULL);
	return (key);
}

/// @brief get element past '=' when export is called.
/// @param *prompt pointer to prompt struct,
/// @param *input address of string of the prompt input,
/// @param *garbage pointer to garbage collector.
/// @return return string containing content of export.
char	*get_content(t_prompt *prompt, char **input, t_garbage *garbage)
{
	char	*content;

	content = ft_strdup(ft_strsep(input, " "));
	ft_add_garbage(0, &garbage, content);
	if (get_char_pos(content, '"') != -1 || get_char_pos(content, 39) != -1)
		check_quotes(prompt, &content, garbage);
	else
		check_is_env_var(&content, garbage);
	return (content);
}


/// @brief In case of export cmd, get and assign every export element.
/// @param *prompt Pointer to prompt struct,
/// @param *input String of the prompt input,
/// @param *garbage Pointer to garbage collector.
void	get_export_args(t_prompt *prompt, char *input, t_garbage *garbage)
{
	int		equal_pos;
	char	*key;
	char	*content;

	prompt->export_args = NULL;
	while (get_char_pos(input, '=') != -1)
	{
		equal_pos = get_char_pos(input, '=');
		if (equal_pos == 0 || ft_isspace(input[equal_pos - 1]))
			return ((void)printf("Bad assignment\n"));
		key = get_key(prompt, &input, garbage);
		content = get_content(prompt, &input, garbage);
		ft_add_export(&prompt->export_args, key, content, garbage);
	}
}
