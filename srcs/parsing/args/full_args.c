/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:50:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/25 22:49:41 by llevasse         ###   ########.fr       */
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

t_arg	**get_this_args(t_prompt *temp, t_arg **new, t_minishell *shell)
{
	int	nb;
	int	i;

	i = 0;
	while (temp)
	{
		nb = 0;
		new[i] = init_arg(shell);
		new[i++]->s = temp->cmd;
		while (temp->args && temp->args[nb] && temp->args[nb]->s)
		{
			new[i] = init_arg(shell);
			new[i++]->s = temp->args[nb++]->s;
		}
		if (!temp->next_cmd)
			break ;
		new[i] = init_arg(shell);
		new[i++]->s = "|";
		temp = temp->next_cmd;
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
