/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:41:08 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/03 14:33:37 by llevasse         ###   ########.fr       */
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
	if (check_is_env_var(&key, prompt->shell) == -1 || key[0] == 0)
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

	content = ft_strdup(*input);
	ft_add_garbage(0, &prompt->garbage, content, prompt->shell);
	if (content[0] == 0 || content[0] == '>' || content[1] == '<')
		return ("");
	if (content[0] != '>' && content[1] != '<')
		check_is_env_var(&content, prompt->shell);
	ft_add_garbage(0, &prompt->garbage, content, prompt->shell);
	return (content);
}

void	get_pos_add(t_prompt *prompt, char *key)
{
	char	*content;
	int		equal_pos;
	int		i;

	i = 0;
	while (prompt->args[i])
	{
		equal_pos = get_char_pos(prompt->args[i]->s, '=');
		if (equal_pos == 0 || ft_isspace(prompt->args[i]->s[equal_pos - 1]))
		{
			write(2, BAD_ID, ft_strlen(BAD_ID));
			errno = 1;
			return ((void)(prompt->cmd = 0));
		}
		key = get_key(prompt, &prompt->args[i]->s);
		content = get_content(prompt, &prompt->args[i]->s);
		ft_add_export(&prompt->export_args, key, content, prompt->shell);
		i++;
	}
	if (!prompt->export_args)
		prompt->cmd = NULL;
}

/// @brief In case of export cmd, get and assign every export element.
/// @param *prompt Pointer to prompt struct,
/// @param *input String of the prompt input,
/// @param *garbage Pointer to garbage collector.
void	get_export_args(t_prompt *prompt)
{
	char	*key;
	char	*input;
	int		i;

	prompt->export_args = NULL;
	i = 0;
	input = prompt->args[i++]->s;
	while (input && get_char_pos(input, '=') == -1)
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
		ft_add_export(&prompt->export_args, key, 0, prompt->shell);
		if (!prompt->args[i])
			break ;
		input = prompt->args[i++]->s;
	}
	get_pos_add(prompt, key);
}
