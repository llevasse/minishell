/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:25:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/08 18:22:48 by llevasse         ###   ########.fr       */
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

void	pass_double_quotes(t_cmd *cmd)
{
	char	*new_str;
	char	*post_quotes;

	cmd->checked = 1;
	//if (check_dollar(cmd->cmd) == -1)

	// WARNING : right now we'll just assume that the input contain two double quotes !
	post_quotes = ft_strchr(cmd->cmd, '"');
	*(post_quotes++) = 0;
	new_str = ft_strjoin(cmd->cmd, post_quotes);
	post_quotes = ft_strchr(new_str, '"');
	*(post_quotes++) = 0;
	new_str = ft_strjoin(new_str, post_quotes);
	cmd->cmd = new_str;
}
