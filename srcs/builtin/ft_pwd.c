/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:07 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 17:18:36 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	val_pwd_prompt(t_prompt *prompt)
{
	if (prompt->full_args[1] && (!ft_strncmp(prompt->full_args[1]->s, "-", 1) \
		&& ft_strncmp(prompt->full_args[1]->s, "-LP", 3)
			&& prompt->full_args[1]->s[1]))
		return (1);
	return (0);
}

/// @brief Print current working directory.
void	ft_pwd(t_prompt *prompt)
{
	char	*new_path;

	if (val_pwd_prompt(prompt))
	{
		new_path = ft_joinf(ERR_PWD, prompt->full_args[1]->s);
		ft_add_garbage(0, &prompt->garbage, new_path, prompt->shell);
		write(2, new_path, ft_strlen(new_path));
		errno = 2;
	}
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
