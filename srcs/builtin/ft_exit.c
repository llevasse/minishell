/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:22 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/20 14:13:43 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

int	is_only_digit(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] || ft_atoi_ullong(s) > 9223372036854775807 || \
		ft_strlen(s) > 19)
		return (0);
	return (1);
}

void	ft_exit(t_garbage *garbage, char **args)
{
	if (!args)
	{
		free_garbage(garbage);
		free_garbage(g_minishell.at_exit_garbage);
		printf(EXIT);
		exit(g_minishell.error_value);
	}
	if (is_only_digit(args[0]) && args[1])
	{
		errno = 1;
		return ((void)ft_printf("minishell : exit : too many arguments\n"));
	}
	if (!is_only_digit(args[0]))
	{
		printf("minishell : exit : numeric argument required\n");
		exit(2);
	}
	printf(EXIT);
	exit((unsigned char)ft_atoi(args[0]));
}
