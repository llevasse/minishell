/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:07 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 17:02:19 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Print current working directory.
void	ft_pwd(t_prompt *prompt)
{
	char	*new_path;

	if (prompt->full_args[1] && !ft_strncmp(prompt->full_args[1]->s, "-", 1) && \
		prompt->full_args[1]->s[1])
		write(2, "Invalid flags for pwd\n", 22);
	else
	{
		new_path = get_pwd(prompt->shell);
		ft_printf("%s\n", new_path);
	}
}

/// @brief Get current working directory path.
char	*get_pwd(t_minishell *shell)
{
	char	*pwd;
	size_t	size;

	size = 128;
	pwd = malloc(sizeof(char) * (size + 1));
	ft_add_garbage(0, &shell->garbage, pwd, shell);
	while (getcwd(pwd, size) == NULL && errno == 36)
	{
		size += 128;
		free(pwd);
		pwd = malloc(sizeof(char) * (size + 1));
		ft_add_garbage(0, &shell->garbage, pwd, shell);
	}
	if (getcwd(pwd, size) != NULL)
		return (getcwd(pwd, size));
	return (NULL);
}
