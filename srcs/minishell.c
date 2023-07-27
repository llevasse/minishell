/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/27 13:23:32 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO signals
// TODO history

int	main(void)
{
	char		*s;
	t_garbage	*garbage;

	garbage = NULL;
	garbage = ft_new_garbage(0, NULL, garbage);
	while (42)
	{
		s = readline("minishell >>");
		add_history(s);
		parse(s, garbage);
	}
}
