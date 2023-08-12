/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:22 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/04 10:33:13 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern struct s_minishell g_minishell;

int	is_only_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (0);
	return (1);
}

void	ft_exit(t_garbage *garbage, char **args)
{
	if (!args)
	{
		free_garbage(garbage);
		exit(g_minishell.error_value);
	}
	if (is_only_digit(args[0]) && args[1])
	{
		errno = 1;
		return ((void)printf("minishell : too many argumentsi\n"));
	}
	if (!is_only_digit(args[0]))
	{
		printf("minishell : too many argumentsi\n");
		exit(2);
	}
	exit((unsigned char)ft_atoi(args[0]));
}
