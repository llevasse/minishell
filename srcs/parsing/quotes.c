/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:25:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/08 19:11:11 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if quotes are present in cmd.
/// @param *cmd Pointer to t_cmd.
/// @return Return 0 if no quotes and 1 if there is.
int	check_quotes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i] && cmd->cmd[i] != '"' && cmd->cmd[i] != '\'')
		i++;
	if (!cmd->cmd[i])
		return (0);
	if (cmd->cmd[i] == '"')
		pass_double_quotes(cmd);
	check_cmd(cmd);
	return (1);
}

/// @brief allocate and assign content of quote to a new str
/// @param *str Str containing quoted content,
/// @param quote Character used as quote.
/// @return Content of quoted str or NULL if error.
char	*get_quoted_str(char *str, char quote)
{
	int i;
	int j;
	char	*new_str;
	
	i = 0;
	j = 0;
	while (str[i] && str[i] != quote)
		i++;
	while (str[i + j] && str[i + j] != quote)
		j++;
	new_str = malloc((j + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	j = 0;
	i++;
	while (str[i + j] != quote)
	{
		new_str[j] = str[i + j];
		j++;
	}
	new_str[j] = 0;
	return (new_str);
}

// WARNING : right now we'll just assume that the input contain two double quotes !
void	pass_double_quotes(t_cmd *cmd)
{
	char	*new_str;
	char	*in_quotes;
	int	i;

	cmd->checked = 1;
	i = 0;
	//if (get_char_pos(cmd->cmd, '$') == -1)
	
	while (cmd->cmd[i] && cmd->cmd[i] != '"')
		i++;
	cmd->cmd[i] = '\0';
	in_quotes = get_quoted_str(cmd->cmd, '"');
	if (!in_quotes)
		return ;
	new_str = ft_strjoin(cmd->cmd, in_quotes);
	cmd->cmd[i++] = '"';
	while (cmd->cmd[i] && cmd->cmd[i] != '"')
		i++;
	new_str = ft_strjoin(new_str, (cmd->cmd + i + 1));
	cmd->cmd = new_str;
}
