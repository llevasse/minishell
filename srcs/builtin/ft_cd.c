/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/17 14:45:26 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_prompt *prompt)
{
	char *new;

	new = NULL;
	if (prompt->args[1] == NULL)
		if (chdir(ft_strjoin("/User/", getenv("USER"))))
			ft_printf("ok\n");
	if (new)
		ft_printf("Cc, je suis cd avec :%s\n", new);
	ft_printf("args[0] = %s,\nargs[1] = %s,\n", prompt->args[0], prompt->args[1]);
}
