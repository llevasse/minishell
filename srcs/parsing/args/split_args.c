/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:29:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/28 18:06:43 by mwubneh          ###   ########.fr       */
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
t_arg	**alloc_tab_args(char const *s, char c, t_minishell *shell)
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
	ft_add_garbage(0, &shell->garbage, res, shell);
	return (res);
}

/// @brief Get next word at index.
/// @param *s String containing every element args before split,
/// @param c Char separating every element in *s,
/// @param i index to search word from,
/// @param *garbage Pointer to garbage collector.
/// @return Return word.
char	*get_word_arg(char const *s, char c, int i, t_minishell *shell)
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
	ft_add_garbage(0, &shell->garbage, res, shell);
	while (j < len_word && s[i] != '\0')
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*get_split_quote(t_prompt *prompt, char **s, int *i)
{
	char	*new;

	new = NULL;
	if ((*s)[*i] == '"')
	{
		new = get_quoted_str(*s + (*i)++, '"', 0, prompt);
		*i += get_char_pos(*s + *i, '"') + 1;
	}
	else if ((*s)[*i] == 39)
	{
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
t_arg	**ft_split_args(t_prompt *prompt, char *s, char c, t_minishell *shell)
{
	t_var_2	var;

	var_set(&var, s, c, shell);
	if (!s || !s[0])
		return (NULL);
	while (s[var.i] != '\0')
	{
		var.res[var.word] = init_arg(shell);
		if (s[var.i] == '"' || s[var.i] == 39)
		{
			if (!go_get_that_quote(prompt, &var, shell))
				return ((void)(errno = 2), NULL);
		}
		else
			get_arg_not_quoted(prompt, &var, shell);
		if (!prompt->cmd && !is_redir_symbol(var.res[var.word], 0) && \
				var.res[var.word])
			prompt->cmd = var.res[var.word]->s;
		we_go_forward(var.res, &var.word, prompt);
		var.i = skip_char(s, c, var.i);
		prompt->full_args = var.res;
	}
	return (var.res);
}
