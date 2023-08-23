/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:29:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/23 19:39:28 by mwubneh          ###   ########.fr       */
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

void	test_3(t_arg **res, int *word, t_prompt *prompt)
{
	(*word)++;
	res[*word] = NULL;
	prompt->args = res;
}

int	test_4(t_prompt *prompt, t_var_2 *var, t_garbage *garbage)
{
	var->res[var->word]->quote = var->str[var->i];
	var->res[var->word]->s = get_split_quote(prompt,
			&var->str, &var->i, var->word - 1);
	if (!prompt->cmd)
		return (0);
	if (var->word > 0 && var->str[var->i - \
			(ft_strlen(var->res[var->word]->s) + 3)] != var->p)
	{
		var->res[var->word - 1]->s = ft_strjoin(var->res[var->word - 1]->s,
				var->res[var->word]->s);
		ft_add_garbage(0, &garbage, var->res[var->word - 1]->s);
		var->res[var->word--] = NULL;
	}
	return (1);
}

void	test_5(t_prompt *prompt, t_var_2 *var, t_garbage *garbage)
{
	var->res[var->word]->s = get_word_arg(var->str, var->p, var->i, garbage);
	var->i += ft_strlen(var->res[var->word]->s);
	check_is_env_var(prompt, &var->res[var->word]->s, garbage);
	if (var->word > 0 && var->str[var->i - \
		(ft_strlen(var->res[var->word]->s) + 1)] != var->p)
	{
		var->res[var->word - 1]->s = ft_strjoin(var->res[var->word - 1]->s, \
			var->res[var->word]->s);
		ft_add_garbage(0, &garbage, var->res[var->word - 1]->s);
		var->res[var->word--] = NULL;
	}
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
	t_var_2	var;

	if (!s || !s[0])
		return (NULL);
	var.str = s;
	var.p = c;
	var.word = 0;
	var.res = alloc_tab_args(s, c, garbage);
	var.i = skip_char(s, c, 0);
	while (s[var.i] != '\0')
	{
		var.res[var.word] = init_arg(garbage);
		if (s[var.i] == '"' || s[var.i] == 39)
		{
			if (!test_4(prompt, &var, garbage))
				return ((void)(errno = 2), NULL);
		}
		else
			test_5(prompt, &var, garbage);
		test_3(var.res, &var.word, prompt);
		var.i = skip_char(s, c, var.i);
	}
	return (var.res);
}
