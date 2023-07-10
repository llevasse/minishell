/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:22 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/10 09:26:40 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_prompt *prompt)
{
	if (prompt->cmd)
		free(prompt->cmd);
	if (prompt->args)
	{
		int i;

		i = -1;
		while(prompt->args[++i])
			free(prompt->args[i]);
		free(prompt->args[i]);
	}
	free(prompt);
	exit(-1);
}
