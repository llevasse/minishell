/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:29:21 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/31 22:09:57 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		s[i + len_word] != '>' && s[i + len_word] != '<')
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

t_arg	*ft_new_arg(char *s, int quote, int dquote, t_garbage *garbage)
{
	t_arg	*new;

	new = malloc(sizeof(struct s_arg));
	ft_add_garbage(0, &garbage, new);
	new->content = s;
	new->dquotes = dquote;
	new->quotes = quote;
	new->id = 0;
	new->next = NULL;
	return (new);
}

void	ft_add_arg(t_arg **lst, char *s, int quote, int dquote, t_garbage *garbage)
{
	t_arg	*temp;
	t_arg	*new;
	int		id;

	id = 0;
	new = ft_new_arg(s, quote, dquote, garbage);
	if (*lst)
	{
		temp = *lst;
		while (temp->next != NULL && id++;)
			temp = temp->next;
		new->id = id;
		temp->next = new;
		return ;
	}
	new->id = id;
	*lst = new;
}

/// @brief Split a string by each c char,
/// but also take account of quotes and other bash specific args.
/// @param *prompt Pointer to prompt struct,
/// @param *s String to split split,
/// @param c Char separating every element in *s,
/// @param *garbage Pointer to garbage collector.
/// @return Return a tab containing every separated element.
t_arg	*ft_split_args(t_prompt *prompt, char *s, char c, t_garbage *garbage)
{
	t_arg	*arg;
	int		i;

	if (!s)
		return (NULL);
	arg = NULL;
	i = skip_char(s, c, 0);
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			if (get_char_occurance(s, '"') % 2 != 0)
				no_end_quote(&s, '"', "dquote>", garbage);
			ft_add_arg(&arg, get_quoted_str(s + i++, '"', 1, garbage), 0, 1, garbage);
			i += get_char_pos(s + i, '"') + 1;
		}
		else if (s[i] == 39)
		{
			if (get_char_occurance(s, 39) % 2 != 0)
				no_end_quote(&s, 39, "quote>", garbage);
			ft_add_arg(&arg, get_quoted_str(s + i++, 39, 1, garbage), 1, 0, garbage);
			i += get_char_pos(s + i, 39) + 1;
		}
		else
		{
			ft_add_arg(&arg, get_word_arg(s, c, i, garbage), 0, 0, garbage);
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		i = skip_char(s, c, i);
	}
	(void)prompt;
	return (arg);
}
