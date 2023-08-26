/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:08 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 15:11:02 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	must_be_valid(char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!ft_isalpha(s1[i]) && s1[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/// @brief get element before '=' when export is called.
/// @param *prompt pointer to prompt struct,
/// @param *input address of string of the prompt input,
/// @param *garbage pointer to garbage collector.
/// @return return string containing key of export.
char	*get_key(t_prompt *prompt, char **input)
{
	char	*key;	

	key = ft_strdup(ft_strsep(input, "="));
	ft_add_garbage(0, &prompt->garbage, key, prompt->shell);
	if (get_char_pos(key, '"') != -1 || get_char_pos(key, 39) != -1)
		check_quotes(prompt, &key);
	else
		check_is_env_var(prompt, &key, prompt->shell);
	if (key[0] == '\0')
		return ((void)printf(BAD_ASS), NULL);
	if (!must_be_valid(key))
	{
		write(2, BAD_ID, ft_strlen(BAD_ID));
		return ((void)(errno = 1), NULL);
	}
	return (key);
}

/// @brief get element past '=' when export is called.
/// @param *prompt pointer to prompt struct,
/// @param *input address of string of the prompt input,
/// @param *garbage pointer to garbage collector.
/// @return return string containing content of export.
char	*get_content(t_prompt *prompt, char **input)
{
	char	*content;

	if (**input == '"')
	{
		no_end_quote(input, '"', W_DQUOTE, prompt->shell);
		content = get_quoted_str(*input, '"', 1, prompt);
	}
	else if (**input == 39)
	{
		no_end_quote(input, 39, W_QUOTE, prompt->shell);
		content = get_quoted_str(*input, 39, 0, prompt);
	}
	else
	{
		content = ft_strdup(ft_strsep(input, " "));
		ft_add_garbage(0, &prompt->garbage, content, prompt->shell);
		if (content[0] != '>' && content[1] != '<')
			check_is_env_var(prompt, &content, prompt->shell);
		if (content[0] == '>' || content[1] == '<')
			return ("");

	}
	ft_add_garbage(0, &prompt->garbage, content, prompt->shell);
	return (content);
}

void	get_pos_add(t_prompt *prompt, char *input, char *key)
{
	char	*content;
	int		equal_pos;

	while (get_char_pos(input, '=') != -1)
	{
		equal_pos = get_char_pos(input, '=');
		if (equal_pos == 0 || ft_isspace(input[equal_pos - 1]))
		{
			write(2, BAD_ID, ft_strlen(BAD_ID));
			errno = 1;
			return ((void)(prompt->cmd = 0));
		}
		key = get_key(prompt, &input);
		content = get_content(prompt, &input);
		ft_add_export(&prompt->export_args, key, content, prompt->shell);
	}
}

/// @brief In case of export cmd, get and assign every export element.
/// @param *prompt Pointer to prompt struct,
/// @param *input String of the prompt input,
/// @param *garbage Pointer to garbage collector.
void	get_export_args(t_prompt *prompt, char *input)
{
	char	*key;

	prompt->export_args = NULL;
	while (get_char_pos(input, '=') == -1)
	{
		key = ft_strdup(ft_strsep(&input, " "));
		ft_add_garbage(0, &prompt->garbage, key, prompt->shell);
		if (key[0] == 0)
			return ;
		if (!must_be_valid(key))
		{
			write(2, BAD_ID, ft_strlen(BAD_ID));
			errno = 1;
			return ((void)(prompt->cmd = 0));
		}
		ft_add_export(&prompt->export_args, NULL, 0, prompt->shell);
	}
	get_pos_add(prompt, input, key);
}
