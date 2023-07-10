/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:22 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/10 00:25:26 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_prompt *cmd)
{
	int	i;

	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
	{
		i = -1;
		while (cmd->args[++i])
			free(cmd->args[i]);
		free(cmd->args[i]);
	}
	free(cmd);
	exit(-1);
}

