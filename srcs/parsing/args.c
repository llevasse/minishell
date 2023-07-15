/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:35:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/15 08:56:17 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get, and assign to t_prompt, args from inputed string.
/// @param *cmd Pointer to t_prompt,
/// @param *input Inputed string to get args from.
void	get_args(t_prompt *prompt, char *input, t_garbage *garbage)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '|')
		i++;
	if (input[i] == '|')
		input[i - 1] = '\0';
	prompt->args = ft_split_args(prompt, input, ' ', garbage);
	if (!prompt->args)
		return (ft_exit(garbage));
	parse_args(prompt, prompt->args, garbage);
	input += i;
}

void	parse_args(t_prompt *prompt, char **args, t_garbage *garbage)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!prompt->d_quotes && !prompt->quotes)
			check_quotes(prompt, &args[i], garbage);
		if (!prompt->quotes)
			check_is_env_var(&args[i], garbage);
		i++;
	}
}

char	**alloc_tab_args(char const *s, char c, t_garbage *garbage)
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
	ft_add_garbage(&garbage, res);
	return (res);
}

char	*get_word_arg(char const *s, char c, int i, t_garbage *garbage)
{
	int		j;
	int		len_word;
	char	*res;

	j = 0;
	len_word = 0;
	while (s[i + len_word] != c && s[i + len_word] != '\0')
		len_word++;
	res = malloc((len_word + 1) * sizeof(char));
	ft_add_garbage(&garbage, res);
	while (j < len_word && s[i] != '\0')
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

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
		if (s[i] == '"')
		{
			prompt->d_quotes = 1;
			no_end_quote(&s + i, '"', "dquote>", garbage); 
			res[index_word] = get_quoted_str(s + i++, '"', 1, garbage);
			i += get_char_pos(s + i, '"') + 1;
		}
		else if (s[i] == 39)
		{
			prompt->quotes = 1;
			no_end_quote(&s + i, 39, "quote>", garbage);
			res[index_word] = get_quoted_str(s + i++, 39, 0, garbage);
			i += get_char_pos(s + i, 39) + 1;
		}
		else
		{
			res[index_word] = get_word_arg(s, c, i, garbage);
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		i = skip_char(s, c, i);
		index_word++;
	}
	res[index_word] = NULL;
	return (res);
}
