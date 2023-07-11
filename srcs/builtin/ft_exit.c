/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:22 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/11 11:26:59 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_prompt *prompt)
{
	int	i;

	if (prompt->cmd)
		free(prompt->cmd);
	if (prompt->args)
	{
		i = -1;
		while (prompt->args[++i])
			free(prompt->args[i]);
		free(prompt->args[i]);
	}
	free(prompt);
	exit(-1);
}
