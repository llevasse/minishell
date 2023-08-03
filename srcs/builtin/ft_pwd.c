/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:07 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/03 15:22:22 by llevasse         ###   ########.fr       */
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

char	*get_pwd(t_garbage *garbage)
{
	char	*pwd;
	size_t	size;

	size = 128;
	pwd = malloc(sizeof(char) * (size + 1));
	ft_add_garbage(0, &garbage, pwd);
	while (getcwd(pwd, size) == NULL && errno == 36)
	{
		size += 128;
		free(pwd);
		pwd = malloc(sizeof(char) * (size + 1));
		ft_add_garbage(0, &garbage, pwd);
	}
	if (getcwd(pwd, size) != NULL)
		return (getcwd(pwd, size));
	return (NULL);
}
