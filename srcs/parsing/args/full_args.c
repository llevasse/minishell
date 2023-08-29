/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:50:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/29 23:42:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_full_args_size(t_prompt *prompt)
{
	int			nb;

	nb = 0;
	nb += get_arg_size(prompt->args) + 2;
	return (nb);
}

t_arg	**get_this_args(t_prompt *temp, t_arg **new, t_minishell *shell)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	new[i] = init_arg(shell);
	new[i++]->s = temp->cmd;
	while (temp->args && temp->args[nb] && temp->args[nb]->s)
	{
		new[i] = init_arg(shell);
		new[i++]->s = temp->args[nb++]->s;
	}
	return (new[i] = NULL, new);
}

t_arg	**get_full_args(t_prompt *prompt, t_minishell *shell)
{
	t_arg		**new;
	t_prompt	*temp;

	temp = prompt;
	new = malloc(get_full_args_size(prompt) * sizeof(t_arg *));
	ft_add_garbage(0, &prompt->garbage, new, prompt->shell);
	new = get_this_args(temp, new, shell);
	return (new);
}
