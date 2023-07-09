/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:26:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/10 00:13:49 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO quotes ?

static void	print_args(char **args, int i);

void	ft_echo(t_prompt *cmd)
{
	if (!cmd->args)
		write(1, "\n", 1);
	else if (cmd->args && !ft_strcmp(cmd->args[0], "-n"))
	{
		if (!cmd->args[1])
			write(1, "", 0);
		else
		{
			print_args(&cmd->args[1], -1);
			write(1, "%\n", 2);
		}
	}
	else
	{
		print_args(cmd->args, -1);
		write(1, "\n", 2);
	}
}

static void	print_args(char **args, int i)
{
	while (args[++i])
	{
		if (i != 0)
			write(1, " ", 1);
		write(1, args[i], ft_strlen(args[i]));
	}
}