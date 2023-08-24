/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:23 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/24 09:58:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

/// @brief add OLDPWD variable to g_minishell.env.
void	add_oldpwd(void)
{
	char	path[PATH_MAX];
	char	*s;

	ft_bzero(path, PATH_MAX);
	s = ft_joinf("OLDPWD=%s", getcwd(path, PATH_MAX));
	ft_add_garbage(1, &g_minishell.at_exit_garbage, s);
	g_minishell.env = insert_at_end(s, g_minishell.env, g_minishell.garbage);
}

/// @brief reproduce unset builtin behavior.
void	ft_unset(t_prompt *prompt)
{
	char	*s;
	int		i;
	int		j;

	if (!prompt->args)
		return ;
	j = 0;
	while (prompt->args[j])
	{
		s = prompt->args[j]->s;
		i = 0;
		while (g_minishell.env[i])
		{
			if (!ft_strncmp(s, g_minishell.env[i], ft_strlen(s)))
			{
				delete_element_at_index(g_minishell.env, i);
				break ;
			}
			i++;
		}
		j++;
	}
}
