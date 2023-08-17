/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:23 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/17 20:13:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

void	add_oldpwd(void)
{
	char	path[PATH_MAX];
	char	*s;

	ft_bzero(path, PATH_MAX);
	s = ft_joinf("OLDPWD=%s", getcwd(path, PATH_MAX));
	ft_add_garbage(0, &g_minishell.at_exit_garbage, s);
	insert_at_end(s, g_minishell.env, g_minishell.garbage);
}

void	ft_unset(t_prompt *prompt)
{
	char	*s;
	int		i;

	if (!prompt->args)
		return ;
	while (prompt->args[0])
	{
		s = prompt->args[0];
		i = 0;
		while (g_minishell.env[i])
		{
			if (!ft_strcmp(s, "PWD"))
				add_oldpwd();
			if (!ft_strncmp(s, g_minishell.env[i], ft_strlen(s)))
			{
				delete_element_at_index(g_minishell.env, i);
				delete_element_at_index(prompt->args, 0);
				break ;
			}
			i++;
		}
	}
}
