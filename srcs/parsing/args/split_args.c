/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:29:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/15 17:22:21 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_arg(char *s, char c, int *i)
{
	int	j;

	j = 0;
	if (s[*i] == 39)
		*i += get_char_pos(s + *i, 39);
	else if (s[*i] == '"')
		*i += get_char_pos(s + *i, '"');
	else
	{
		while (s[*i] && s[*i] != c && s[*i] != 39 && s[*i] != '"')
		{
			if (s[*i] == '|')
				return (j);
			if (s[*i] == '>' || s[*i] == '<')
				j++;
			(*i)++;
		}
	}
	return (j);
}

/// @brief Allocate enough memory for tab based on numbers of elements in *s.
/// @param *s String containing every element args before split,
/// @param c Char separating every element in *s,
/// @param *garbage Pointer to garbage collector.
/// @return Return allocated pointer of char *.
char	**alloc_tab_args(char const *s, char c, t_garbage *garbage)
{
	int		i;
	int		j;
	char	**res;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		i = skip_char(s, c, i);
		if (!s[i])
			break ;
		if (s[i] && (s[i] != c || s[i] == 39 || s[i] == '"'))
		{
			j++;
			j += skip_arg((char *)s, c, &i);
			if (s[i] == '|')
				break ;
		}
		if (!s[i])
			break ;
		i++;
	}
	res = malloc((j + 1) * sizeof(char *));
	ft_add_garbage(0, &garbage, res);
	return (res);
}

/// @brief Get next word at index.
/// @param *s String containing every element args before split,
/// @param c Char separating every element in *s,
/// @param i index to search word from,
/// @param *garbage Pointer to garbage collector.
/// @return Return word.
char	*get_word_arg(char const *s, char c, int i, t_garbage *garbage)
{
	int		j;
	int		len_word;
	char	*res;

	j = 0;
	len_word = 0;
	if (s[i] == '>' || s[i] == '<')
		len_word++;
	if (s[i + 1] == '>' || s[i + 1] == '<')
		len_word++;
	while (s[i + len_word] != c && s[i + len_word] != '\0' && \
		s[i + len_word] != '>' && s[i + len_word] != '<' && \
		s[i + len_word] != '|')
		len_word++;
	res = malloc((len_word + 1) * sizeof(char));
	ft_add_garbage(0, &garbage, res);
	while (j < len_word && s[i] != '\0')
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*get_split_quote(t_prompt *prompt, char *s, int *i, t_garbage *garbage)
{
	char	*new;

	new = NULL;
	if (s[*i] == '"')
	{
		prompt->d_quotes = 1;
		if (get_char_occurance(s, '"') % 2 != 0)
			no_end_quote(&s, '"', W_DQUOTE, garbage);
		new = get_quoted_str(s + (*i)++, '"', 1, garbage);
		*i += get_char_pos(s + *i, '"') + 1;
	}
	else if (s[*i] == 39)
	{
		prompt->quotes = 1;
		if (get_char_occurance(s, 39) % 2 != 0)
			no_end_quote(&s, 39, W_QUOTE, garbage);
		new = get_quoted_str(s + (*i)++, 39, 0, garbage);
		*i += get_char_pos(s + *i, 39) + 1;
	}
	return (new);
}

/// @brief Split a string by each c char,
/// but also take account of quotes and other bash specific args.
/// @param *prompt Pointer to prompt struct,
/// @param *s String to split split,
/// @param c Char separating every element in *s,
/// @param *garbage Pointer to garbage collector.
/// @return Return a tab containing every separated element.
char	**ft_split_args(t_prompt *prompt, char *s, char c, t_garbage *garbage)
{
	char	**res;
	int		i;
	int		index_word;

	if (!s)
		return (NULL);
	index_word = 0;
	res = alloc_tab_args(s, c, garbage);
	i = skip_char(s, c, 0);
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == 39)
			res[index_word] = get_split_quote(prompt, s, &i, garbage);
		else
		{
			res[index_word] = get_word_arg(s, c, i, garbage);
			i += ft_strlen(res[index_word]);
		}
		index_word++;
		i = skip_char(s, c, i);
	}
	return ((void)(res[index_word] = NULL), res);
}
