/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:26:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/21 15:21:39 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(t_arg **args, int i);

void	ft_echo(t_prompt *prompt)
{
	if (!prompt->args)
		write(1, "\n", 1);
	else if (prompt->args[0] && !ft_strcmp(prompt->args[0]->s, "-n"))
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

static void	print_args(t_arg **args, int i)
{
	while (args[++i])
	{
		if (i != 0)
			write(1, " ", 1);
		write(STDOUT_FILENO, args[i]->s, ft_strlen(args[i]->s));
	}
}
