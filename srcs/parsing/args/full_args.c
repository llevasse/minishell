/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:50:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/23 11:07:28 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_full_args_size(t_prompt *prompt)
{
	int			nb;
	t_prompt	*temp;

	nb = 0;
	temp = prompt;
	while (temp)
	{
		nb += get_arg_size(temp->args) + 2;
		temp = temp->next_cmd;
	}
	return (nb);
}

t_arg	**get_this_args(t_prompt *temp, t_arg **new, t_garbage *garbage)
{
	int	nb;
	int	i;

	i = 0;
	while (temp)
	{
		nb = 0;
		new[i] = init_arg(garbage);
		new[i++]->s = temp->cmd;
		while (temp->args && temp->args[nb] && temp->args[nb]->s)
		{
			new[i] = init_arg(garbage);
			new[i++]->s = temp->args[nb++]->s;
		}
		if (!temp->next_cmd)
			break ;
		new[i] = init_arg(garbage);
		new[i++]->s = "|";
		temp = temp->next_cmd;
	}
	return (new[i] = NULL, new);
}

t_arg	**get_full_args(t_prompt *prompt, t_garbage *garbage)
{
	t_arg		**new;
	t_prompt	*temp;

	temp = prompt;
	new = malloc(get_full_args_size(prompt) * sizeof(t_arg *));
	ft_add_garbage(0, &garbage, new);
	new = get_this_args(temp, new, garbage);
	return (new);
}
