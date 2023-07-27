/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:07 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/27 12:52:25 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern char	**environ;


//currently pwd, recovers the cwd and overwrites it, so that it is up-to-date,
// and existing if it has been unset.
void	ft_pwd(void)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	setenv("PWD", path, 1);
	ft_printf("%s\n", getenv("PWD"));
}
