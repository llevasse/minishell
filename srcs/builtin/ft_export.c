/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/30 16:50:44 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf("Je vais assigne la key \"%s\" au content \"%s\"\n",
				temp->key, temp->content);
		else
			printf("Je vais imprimer une liste des exports\n");
		temp = temp->next;
	}
}
