/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:35:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/10 23:13:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get, and assign to t_prompt, args from inputed string.
/// @param *cmd Pointer to t_prompt,
/// @param *input Inputed string to get args from.
void	get_args(t_prompt *prompt, char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '|')
		i++;
	if (input[i] == '|')
		input[i - 1] = '\0';
	prompt->args = ft_split_args(prompt, input, ' ');
	if (!prompt->args)
		return (free(prompt));
	parse_args(prompt, prompt->args);
	input += i;
}

void	parse_args(t_prompt *prompt, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!prompt->d_quotes && !prompt->quotes)
			check_quotes(prompt, &args[i]);
		if (!prompt->quotes)
			check_is_env_var(&args[i]);
		i++;
	}
}

char	**alloc_tab_args(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] && (s[i] != c || s[i] == 39 || s[i] == '"'))
			j++;
		i++;
		while (s[i] && s[i] != c && s[i] == 39 && s[i] != '"')
			i++;
	}
	res = malloc((j + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (res);
}

char	**ft_split_args(t_prompt *prompt, char const *s, char c)
{
	char	**res;
	int		i;
	int		index_word;

	if (!s)
		return (NULL);
	index_word = 0;
	res = alloc_tab_args(s, c);
	if (!res)
		return (NULL);
	i = skip_char(s, c, 0);
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			prompt->d_quotes = 1;
			res[index_word] = get_quoted_str((char *)s + i++, '"', 1);
			if (!res[index_word])
				return (free_tab(res, index_word));
			i += get_char_pos((char *)s + i, '"') + 1;
		}
		else if (s[i] == 39)
		{
			prompt->quotes = 1;
			res[index_word] = get_quoted_str((char *)s + i++, 39, 0);
			if (!res[index_word])
				return (free_tab(res, index_word));
			i += get_char_pos((char *)s + i, 39) + 1;
		}
		else
		{
			res[index_word] = get_word(s, c, i);
			if (!res[index_word])
				return (free_tab(res, index_word));
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		i = skip_char(s, c, i);
		index_word++;
	}
	res[index_word] = NULL;
	return (res);
}
