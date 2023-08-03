/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:26:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/27 10:51:34 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	print_args(char **args, int i);

void	ft_echo(t_prompt *prompt)
{
	if (!prompt->args)
		write(1, "\n", 1);
	else if (prompt->args && !ft_strcmp(prompt->args[0], "-n"))
	{
		if (!prompt->args[1])
			write(1, "", 0);
		else
		{
			print_args(&prompt->args[1], -1);
			write(1, "%\n", 2);
		}
	}
	else
	{
		print_args(prompt->args, -1);
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
