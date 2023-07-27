/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/27 11:00:57 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO signals
// TODO history

int	main(void)
{
	t_garbage	*garbage;

	garbage = NULL;
	garbage = ft_new_garbage(0, NULL, garbage);
	while (42)
		parse(readline("minishell >>"), garbage);
}
