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

#include "minishell.h"

extern struct s_minishell	g_minishell;

static char	*get_current_dir(char **environ);

void	ft_pwd(t_prompt *prompt)
{
	char	*new_path;
	new_path = get_current_dir(prompt->environ);
	ft_printf("%s\n", new_path);
	ft_add_garbage(0, &g_minishell.at_exit_garbage, new_path);
	delete_duplicate_export("PWD");
	g_minishell.env = insert_at_end(new_path,
									g_minishell.env, g_minishell.at_exit_garbage);
}

static char	*get_current_dir(char **environ)
{
	int	i;

	i = -1;
	while (environ[++i] && ft_strncmp(environ[i], "PWD=", 4))
		;
	return (&environ[i][4]);
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
