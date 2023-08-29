/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:50:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/29 23:47:04 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	**get_full_args(t_prompt *prompt, t_minishell *shell)
{
	t_arg		**new;
	int			nb;
	int			i;

	new = malloc((get_arg_size(prompt->args) + 2) * sizeof(t_arg *));
	ft_add_garbage(0, &prompt->garbage, new, prompt->shell);
	i = 0;
	nb = 0;
	new[i] = init_arg(shell);
	new[i++]->s = prompt->cmd;
	while (prompt->args && prompt->args[nb] && prompt->args[nb]->s)
	{
		new[i] = init_arg(shell);
		new[i++]->s = prompt->args[nb++]->s;
	}
	return (new[i] = NULL, new);
}
