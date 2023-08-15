/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:50:33 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/15 14:51:12 by llevasse         ###   ########.fr       */
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
		nb += get_tab_size(temp->args) + 2;
		temp = temp->next_cmd;
	}
	return (nb);
}

char	**get_full_args(t_prompt *prompt, t_garbage *garbage)
{
	int			nb;
	int			i;
	char		**new;
	t_prompt	*temp;

	temp = prompt;
	i = 0;
	new = malloc(get_full_args_size(prompt) * sizeof(char **));
	ft_add_garbage(0, &garbage, new);
	while (temp)
	{
		nb = 0;
		new[i++] = temp->cmd;
		while (temp->args && temp->args[nb])
			new[i++] = temp->args[nb++];
		if (!temp->next_cmd)
			break ;
		new[i++] = "|";
		temp = temp->next_cmd;
	}
	return (new[i] = NULL, new);
}
