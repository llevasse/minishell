/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:29:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/21 20:46:19 by llevasse         ###   ########.fr       */
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
t_arg	**alloc_tab_args(char const *s, char c, t_garbage *garbage)
{
	int		i;
	int		j;
	t_arg	**res;

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
	res = malloc((j + 1) * sizeof(struct s_arg *));
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
	while (s[i + len_word] && s[i + len_word] != c && \
		!ft_is_in_str("<>|'\"", s[i + len_word]))
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

char	*get_split_quote(t_prompt *prompt, char **s, int *i, int index_word)
{
	char	*new;

	new = NULL;
	if ((*s)[*i] == '"')
	{
		if (get_char_occurance(*s, '"') % 2 != 0)
			no_end_quote(s, '"', W_DQUOTE, prompt->garbage);
		if ((*s)[0] == 0)
			return ((void)(prompt->cmd = NULL), NULL);
		if (index_word >= 0 && !ft_strcmp(prompt->args[index_word]->s, "<<"))
			new = get_quoted_str(*s + (*i)++, '"', 0, prompt);
		else
			new = get_quoted_str(*s + (*i)++, '"', 1, prompt);
		*i += get_char_pos(*s + *i, '"') + 1;
	}
	else if ((*s)[*i] == 39)
	{
		if (get_char_occurance(*s, 39) % 2 != 0)
			no_end_quote(s, 39, W_QUOTE, prompt->garbage);
		new = get_quoted_str(*s + *i, 39, 0, prompt);
		*i += get_char_pos(*s + *i + 1, 39) + 2;
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
t_arg	**ft_split_args(t_prompt *prompt, char *s, char c, t_garbage *garbage)
{
	t_arg	**res;
	int		i;
	int		word;

	if (!s || !s[0])
		return (NULL);
	word = 0;
	res = alloc_tab_args(s, c, garbage);
	i = skip_char(s, c, 0);
	while (s[i] != '\0')
	{
		res[word] = init_arg(garbage);
		if (s[i] == '"' || s[i] == 39)
		{
			res[word]->quote = s[i];
			res[word]->s = get_split_quote(prompt, &s, &i, word - 1);
			if (!prompt->cmd)
				return ((void)(errno = 2), NULL);
			if (word > 0 && s[i - (ft_strlen(res[word]->s) + 3)] != c)
			{
				res[word - 1]->s = ft_strjoin(res[word - 1]->s,
										res[word]->s);
				ft_add_garbage(0, &garbage, res[word - 1]->s);
				res[word--] = NULL;
			}
		}
		else
		{
			res[word]->s = get_word_arg(s, c, i, garbage);
			i += ft_strlen(res[word]->s);
			check_is_env_var(prompt, &res[word]->s, garbage);
			if (word > 0 && s[i - (ft_strlen(res[word]->s) + 1)] != c)
			{
				res[word - 1]->s = ft_strjoin(res[word - 1]->s,
										res[word]->s);
				ft_add_garbage(0, &garbage, res[word - 1]->s);
				res[word--] = NULL;
			}
		}
		word++;
		res[word] = NULL;
		prompt->args = res;
		i = skip_char(s, c, i);
	}
	return (res);
}
