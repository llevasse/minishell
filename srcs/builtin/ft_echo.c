/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:26:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/23 23:16:13 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(t_arg **args, int i);
static int	is_n_flag(char *s);

/// @brief recreation of the echo cmd,
/// print passed argument.
/// @param *prompt pointer to prompt struct containing the args to print.
void	ft_echo(t_prompt *prompt)
{
	if (!prompt->args)
		write(1, "\n", 1);
	else if (prompt->args[0] && is_n_flag(prompt->args[0]->s))
	{
		if (!prompt->args[1])
			write(1, "", 0);
		else
			print_args(&prompt->args[1], -1);
	}
	else
	{
		print_args(prompt->args, -1);
		write(1, "\n", 2);
	}
}

/// @brief Check if *s is valid -n echo flag.
static int	is_n_flag(char *s)
{
	int	i;

	i = 1;
	if (s[0] == '-')
	{
		while (s[i] && s[i] == 'n')
			i++;
		if (!s[i])
			return (1);
	}
	return (0);
}

/// @brief Print arguments from a certain index.
/// @param **args Array of t_arg variable to print,
/// @param i index to print from (-1 if from the begining).
static void	print_args(t_arg **args, int i)
{
	while (args[++i])
	{
		if (i != 0)
			write(1, " ", 1);
		write(STDOUT_FILENO, args[i]->s, ft_strlen(args[i]->s));
	}
}
