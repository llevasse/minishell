/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:25:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/27 11:29:42 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if quotes are present in cmd.
/// @param *cmd Pointer to t_prompt.
/// @return Return 0 if no quotes and 1 if there is.
int	check_quotes(t_prompt *prompt, char **str)
{
	int	i;

	i = 0;
	if (get_char_pos(*str, '"') == -1 && get_char_pos(*str, 39) == -1)
		return (0);
	while ((*str)[i] && (*str)[i] != '"' && (*str)[i] != 39)
		i++;
	if (!(*str)[i])
		return (0);
	if ((*str)[i] == '"')
		pass_double_quotes(prompt, str);
	else if ((*str)[i] == 39)
		pass_single_quotes(prompt, str);
	return (1);
}

int	get_true_nb_quotes(char *str)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == 39 || str[i] == '"')
			j++;
		if (str[i] == '\\')
			i += 2;
		else
			i++;
	}
	return (j);
}

/// @brief allocate and assign content of quote to a new str
/// @param *str Str containing quoted content,
/// @param quote Character used as quote.
/// @param env_var 1 if checking for env var, and 0 if not 
/// @return Content of quoted str or NULL if error.
char	*get_quoted_str(char *str, char quote, int env_var, t_prompt *prompt)
{
	int		i;
	int		j;
	char	*new_str;

	i = get_char_pos(str, quote);
	j = get_char_pos(str + i + 1, quote);
	if (get_char_occurance(str, quote) % 2 != 0)
		j = ft_strlen(str + i);
	if (j > i)
		j -= i;
	else
		j = i - j;
	new_str = malloc((j + 1) * sizeof(char));
	ft_add_garbage(0, &prompt->garbage, new_str, prompt->shell);
	j = 0;
	i++;
	while (str[i + j] && str[i + j] != quote)
	{
		new_str[j] = str[i + j];
		j++;
	}
	new_str[j] = 0;
	if (env_var)
		check_is_env_var(prompt, &new_str, prompt->shell);
	return (new_str);
}

/// @brief Replace doubles quotes with it's content
/// @param *prompt Pointer prompt struct,
/// @param **str Pointer to str containing at least one d_quote,
/// @param *garbage Pointer to garbage struct. 
void	pass_double_quotes(t_prompt *prompt, char **str)
{
	char	*new_str;
	char	*in_quotes;
	int		i;

	i = get_char_pos(*str, '"');
	in_quotes = get_quoted_str(*str, '"', 1, prompt);
	if (!in_quotes)
		return ;
	*str[i] = 0;
	new_str = ft_strjoin(*str, in_quotes);
	ft_add_garbage(0, &prompt->garbage, new_str, prompt->shell);
	i = get_char_pos(*str + i, '"');
	new_str = ft_strjoin(new_str, (*str + i + 1));
	ft_add_garbage(0, &prompt->garbage, new_str, prompt->shell);
	*str = new_str;
}

/// @brief Replace single quotes with it's content
/// @param *prompt Pointer prompt struct,
/// @param **str Pointer to str containing at least one quote,
/// @param *garbage Pointer to garbage struct. 
void	pass_single_quotes(t_prompt *prompt, char **str)
{
	char	*original_quote;
	char	*in_quotes;
	int		i;

	i = get_char_pos(*str, (char)39);
	original_quote = ft_strdup(*str + i);
	ft_add_garbage(0, &prompt->garbage, original_quote, prompt->shell);
	original_quote[get_char_pos(original_quote + 1, 39) + 2] = '\0';
	in_quotes = get_quoted_str(*str, (char)39, 0, prompt);
	replace_str(str, original_quote, in_quotes, prompt->shell);
}


// check what is a valid quote (\" is not considered a quote)
