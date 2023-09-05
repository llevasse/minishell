/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:52:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/05 22:50:42 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Allocate memory and assign values to t_prompt.
/// @param *input Inputed string to get command from.
/// @return Return pointer to t_prompt or NULL if something failed.
t_arg	*init_arg(t_minishell *shell)
{
	t_arg	*arg;

	arg = malloc(sizeof(struct s_arg));
	ft_add_garbage(0, &shell->garbage, arg, shell);
	arg->quote = 0;
	arg->joined_quote = 0;
	arg->s = 0;
	return (arg);
}

char	**to_char_array(t_arg **args, t_minishell *shell)
{
	char	**new;
	int		i;

	new = malloc((get_arg_size(args) + 1) * sizeof(char *));
	ft_add_garbage(0, &shell->garbage, new, shell);
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
	while (tab && tab[i] && tab[i]->s)
		i++;
	return (i);
}
