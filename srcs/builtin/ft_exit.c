/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:22 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/09 14:18:09 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_prompt *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
	{
		int i;

		i = -1;
		while(cmd->args[++i])
			free(cmd->args[i]);
		free(cmd->args[i]);
	}
	free(cmd);
	exit(-1);
}

