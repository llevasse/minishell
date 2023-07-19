/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:25:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/19 11:02:29 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if quotes are present in cmd.
/// @param *cmd Pointer to t_prompt.
/// @return Return 0 if no quotes and 1 if there is.
int	check_quotes(t_prompt *prompt, char **str, t_garbage *garbage)
{
	int	i;

	i = 0;
	if (get_char_pos(*str, '"') == -1 && get_char_pos(*str, 39) == -1)
		return (0);
	while (*str[i] && *str[i] != '"' && *str[i] != 39)
		i++;
	if (!*str[i])
		return (0);
	if (*str[i] == '"')
		pass_double_quotes(prompt, str, garbage);
	else if (*str[i] == 39)
		pass_single_quotes(prompt, str, garbage);
	return (1);
}

/// @brief Check if the prompt cmd has a full quote.
/// @param *prompt Pointer to t_prompt,
/// @param quote Character showing begining and end of quote,
/// @param *to_print String to print as prompt while the quote is not ended.
/// @return Do nothing if quote is full, 
/// otherwise create an infinte loop until quote ends.
void	no_end_quote(char **str, char quote, char *to_print, t_garbage *garbage)
{
	char	*new_str;
	int		i;

	i = get_char_pos(*str, quote);
	while (get_char_pos(*str + i + 1, quote) == -1)
	{
		new_str = readline(to_print);
		*str = ft_strjoin(*str, "\n");
		ft_add_garbage(&garbage, *str);
		if (*new_str != '\0')
			*str = ft_strjoin(*str, new_str);
		free(new_str);
		new_str = NULL;
		ft_add_garbage(&garbage, *str);
	}
}

/// @brief allocate and assign content of quote to a new str
/// @param *str Str containing quoted content,
/// @param quote Character used as quote.
/// @param env_var 1 if checking for env var, and 0 if not 
/// @return Content of quoted str or NULL if error.
char	*get_quoted_str(char *str, char quote, int env_var, t_garbage *garbage)
{
	int		i;
	int		j;
	char	*new_str;

	i = get_char_pos(str, quote);
	j = get_char_pos(str + i + 1, quote) - i;
	new_str = malloc((j + 1) * sizeof(char));
	ft_add_garbage(&garbage, new_str);
	j = 0;
	i++;
	while (str[i + j] && str[i + j] != quote)
	{
		new_str[j] = str[i + j];
		j++;
	}
	new_str[j] = 0;
	if (env_var)
		check_is_env_var(&new_str, garbage);
	return (new_str);
}

void	pass_double_quotes(t_prompt *prompt, char **str, t_garbage *garbage)
{
	char	*new_str;
	char	*in_quotes;
	int		i;

	prompt->d_quotes = 1;
	no_end_quote(str, '"', "dquote>", garbage);
	i = get_char_pos(*str, '"');
	in_quotes = get_quoted_str(*str, '"', 1, garbage);
	if (!in_quotes)
		return ;
	*str[i] = 0;
	new_str = ft_strjoin(*str, in_quotes);
	ft_add_garbage(&garbage, new_str);
	i = get_char_pos(*str + i, '"');
	new_str = ft_strjoin(new_str, (*str + i + 1));
	ft_add_garbage(&garbage, new_str);
	*str = new_str;
}

void	pass_single_quotes(t_prompt *prompt, char **str, t_garbage *garbage)
{
	char	*original_quote;
	char	*in_quotes;
	int		i;

	prompt->quotes = 1;
	no_end_quote(str, (char)39, "quote>", garbage);
	i = get_char_pos(*str, (char)39);
	original_quote = ft_strdup(*str + i);
	ft_add_garbage(&garbage, original_quote);
	original_quote[get_char_pos(original_quote + 1, 39) + 2] = '\0';
	in_quotes = get_quoted_str(*str, (char)39, 0, garbage);
	replace_str(str, original_quote, in_quotes, garbage);
}
