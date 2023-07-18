/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/18 21:51:12 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_prompt *prompt)
{
	printf("Cc, je suis ft_export.\n");
	if (prompt->export_args)
		printf("Si prompt->export_args n'est pas null\n\
Je vais assigne la key |%s| a |%s|\n", prompt->export_args->key, prompt->export_args->content);
	else
		printf("Si prompt->export_args est null\nJe vais imprimer une liste des exports\n");
}
