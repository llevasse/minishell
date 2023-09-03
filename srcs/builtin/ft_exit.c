/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:22 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/03 22:19:16 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief check is *s is valid param for exit.
/// @param *s String to check.
/// @return Return 1 if valid and 0 if not.
int	is_only_digit(char *s)
{
	int	i;

	i = 0;
	while (ft_isspace(*s) == 1)
		s++;
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[0] == '-' && ft_atoi_ullong(s) - 1 <= 9223372036854775807)
		return (1);
	if (s[i] || ft_atoi_ullong(s) > 9223372036854775807 || ft_strlen(s) > 19)
		return (0);
	return (1);
}

void	exit_with_one(t_minishell *shell)
{
//	int	i;

//	i = -1;
	free_garbage(shell->garbage);
	free_garbage(shell->at_exit_garbage);
	printf(EXIT);
	write(2, NOT_NUM_ARG, ft_strlen(NOT_NUM_ARG));
//	while (++i < 1024)
//		close(i);
	exit(2);
}

/// @brief Reproduace exit builtin behavior.
/// @param *garbage Pointer to garbage collector,
/// @param **args array of t_arg pointer. 
void	ft_exit(t_minishell *shell, t_arg **args)
{
//	int	i;

//	i = -1;
	if (!args || !args[0])
	{
		free_garbage(shell->garbage);
		free_garbage(shell->at_exit_garbage);
		printf(EXIT);
//		while (++i < 1024)
//			close(i);
		exit(shell->error_value);
	}
	if (is_only_digit(args[0]->s) && args[1])
	{
		errno = 1;
		return ((void)write(2, TMA, ft_strlen(TMA)));
	}
	if (!is_only_digit(args[0]->s))
		exit_with_one(shell);
//	while (++i < 1024)
//		close(i);
	printf(EXIT);
	exit((unsigned char)ft_atoi(args[0]->s));
}
