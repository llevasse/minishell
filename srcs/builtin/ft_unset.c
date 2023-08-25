/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:23 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 00:14:38 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief add OLDPWD variable to shell->env.
void	add_oldpwd(t_minishell *shell)
{
	char	path[PATH_MAX];
	char	*s;

	ft_bzero(path, PATH_MAX);
	s = ft_joinf("OLDPWD=%s", getcwd(path, PATH_MAX));
	ft_add_garbage(1, &shell->at_exit_garbage, s, shell);
	shell->env = insert_at_end(s, shell->env, shell);
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
		while (prompt->shell->env[i])
		{
			if (!ft_strncmp(s, prompt->shell->env[i], ft_strlen(s)))
			{
				delete_element_at_index(prompt->shell->env, i);
				break ;
			}
			i++;
		}
		j++;
	}
}
