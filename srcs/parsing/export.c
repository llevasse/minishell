/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:08 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/17 22:01:37 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		check_is_env_var(prompt, &key, garbage);
	if (key[0] == '\0')
		return ((void)printf(BAD_ASS), NULL);
	if (get_char_pos(key, '$') != -1)
		return ((void)printf(BAD_KEY, key), NULL);
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

	if (**input == '"')
	{
		prompt->d_quotes = 1;
		no_end_quote(input, '"', W_DQUOTE, garbage);
		content = get_quoted_str(*input, '"', 1, prompt);
	}
	else if (**input == 39)
	{
		prompt->quotes = 1;
		no_end_quote(input, 39, W_QUOTE, garbage);
		content = get_quoted_str(*input, 39, 0, prompt);
	}
	else
	{
		content = ft_strdup(ft_strsep(input, " "));
		check_is_env_var(prompt, &content, garbage);
	}
	ft_add_garbage(0, &garbage, content);
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
	if (get_char_pos(input, '=') == -1)
	{
		key = ft_strdup(input);
		ft_add_garbage(0, &garbage, key);
		ft_add_export(&prompt->export_args, ft_strsep(&input, " "), 0, garbage);
	}
	while (get_char_pos(input, '=') != -1)
	{
		equal_pos = get_char_pos(input, '=');
		if (equal_pos == 0 || ft_isspace(input[equal_pos - 1]))
			return ((void)printf(BAD_ASS));
		key = get_key(prompt, &input, garbage);
		content = get_content(prompt, &input, garbage);
		ft_add_export(&prompt->export_args, key, content, garbage);
	}
}
