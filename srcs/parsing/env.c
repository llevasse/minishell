/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/07 11:35:55 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_in_env(char *cmd)
{
	char *path;

	path = getenv("PATH");
	printf("PATH : %s\n", path);
	(void)cmd;
	return (1);
}
