/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:52:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/20 21:06:23 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

/// @brief Allocate memory and assign values to t_prompt.
/// @param *input Inputed string to get command from.
/// @return Return pointer to t_prompt or NULL if something failed.
t_arg	*init_arg(t_garbage *garbage)
{
	t_arg	*arg;

	arg = malloc(sizeof(struct s_arg));
	ft_add_garbage(0, &garbage, arg);
	arg->quote = 0;
	arg->s = 0;
	return (arg);
}

char	**to_char_array(t_arg **args, t_garbage *garbage)
{
	char	**new;
	int		i;

	new = malloc((get_arg_size(args) + 1) * sizeof(char *));
	ft_add_garbage(0, &garbage, new);
	i = -1;
	while (args[++i])
		new[i] = args[i]->s;
	new[i] = 0;
	return (new);
}

/// @brief Get number of element in **tab.
/// @param **tab Pointer to pointers of char.
/// @return Return number of element in tab.
int	get_arg_size(t_arg **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
