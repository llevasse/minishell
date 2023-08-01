/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/01 12:41:02 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export(t_prompt *prompt)
{
	t_export	*temp;

	printf("Cc, je suis ft_export.\n");
	temp = prompt->export_args;
	while (temp)
	{
		if (!temp->key)
			return ;
		if (temp)
		{
			setenv(temp->key, temp->content, 1);
		}
		else
			printf("Je vais imprimer une liste des exports\n");
		temp = temp->next;
	}
}
