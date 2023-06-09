/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:25:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/09 19:54:34 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if quotes are present in cmd.
/// @param *cmd Pointer to t_prompt.
/// @return Return 0 if no quotes and 1 if there is.
int	check_quotes(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt->cmd[i] && prompt->cmd[i] != '"' && prompt->cmd[i] != '\'')
		i++;
	if (!prompt->cmd[i])
		return (0);
	if (prompt->cmd[i] == '"')
		pass_double_quotes(prompt);
	else if (prompt->cmd[i] == 39)
		pass_single_quotes(prompt);
	check_cmd(prompt);
	return (1);
}


/// @brief Check if the prompt cmd has a full quote.
/// @param *prompt Pointer to t_prompt,
/// @param quote Character showing begining and end of quote,
/// @param *to_print String to print as prompt while the quote is not ended.
/// @return Do nothing if quote is full, 
/// otherwise create an infinte loop until quote ends.
void	no_end_quote(t_prompt *prompt, char quote, char *to_print)
{
	char	*new_str;
	int	i;

	i = get_char_pos(prompt->cmd, quote);
	while (get_char_pos(prompt->cmd + i + 1, quote) == -1)
	{
		new_str = readline(to_print);
		if (!new_str)
			prompt->cmd = "error";
		prompt->cmd = ft_strjoin(prompt->cmd, "\n");
		if (*new_str != '\0')
			prompt->cmd = ft_strjoin(prompt->cmd, new_str);
		free(new_str);
		new_str = NULL;
		if (!prompt->cmd)
			prompt->cmd = "error";
	}

}

/// @brief allocate and assign content of quote to a new str
/// @param *str Str containing quoted content,
/// @param quote Character used as quote.
/// @param env_var 1 if checking for env var, and 0 if not 
/// @return Content of quoted str or NULL if error.
char	*get_quoted_str(char *str, char quote, int env_var)
{
	int		i;
	int		j;
	char	*new_str;

	i = get_char_pos(str, quote);
	j = get_char_pos(str + i + 1, quote) - i;
	new_str = malloc((j + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	j = 0;
	i++;
	while (str[i + j] && str[i + j] != quote)
	{
		new_str[j] = str[i + j];
		j++;
	}
	new_str[j] = 0;
	if (env_var)
		check_is_env_var(&new_str);
	return (new_str);
}

void	pass_double_quotes(t_prompt *prompt)
{
	char	*new_str;
	char	*in_quotes;
	int		i;

	prompt->d_quotes = 1;
	no_end_quote(prompt, '"', "dquote>");
	i = get_char_pos(prompt->cmd, '"');
	in_quotes = get_quoted_str(prompt->cmd, '"', 1);
	if (!in_quotes)
		return ;
	prompt->cmd[i] = 0;
	new_str = ft_strjoin(prompt->cmd, in_quotes);
	i = get_char_pos(prompt->cmd + i, '"');
	new_str = ft_strjoin(new_str, (prompt->cmd + i + 1));
	prompt->cmd = new_str;
}

void	pass_single_quotes(t_prompt *prompt)
{
	char	*new_str;
	char	*in_quotes;
	int		i;

	prompt->quotes = 1;
	no_end_quote(prompt, (char)39, "quote>");
	i = get_char_pos(prompt->cmd, (char)39);
	in_quotes = get_quoted_str(prompt->cmd, (char)39, 0);
	if (!in_quotes)
		return ;
	prompt->cmd[i] = 0;
	new_str = ft_strjoin(prompt->cmd, in_quotes);
	i = get_char_pos(prompt->cmd + i, (char)39);
	new_str = ft_strjoin(new_str, (prompt->cmd + i + 1));
	prompt->cmd = new_str;
}
