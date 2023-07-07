/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/07 23:47:32 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if cmd in a command present in env.
/// @return If cmd is found return 1 else 0.
int	check_cmd_in_env(char *cmd)
{
	char	*path;
	int	has_exec;
	char	*p_path;

	has_exec = 0;
	path = ft_strdup(getenv("PATH"));
	if (!path)
		return (0);
	p_path = path;
	while (*path && !has_exec)
		has_exec = check_present_in_path(cmd, ft_strsep(&path, ":"));
	return ((void)p_path, has_exec);
}

/// @brief Check if cmd in a command present in path.
/// @return If cmd is found return 1 else 0.
int	check_present_in_path(char *cmd, char *path)
{
	DIR		*current_dir;
	struct dirent	*dir_entry;

	current_dir = opendir(path);
	if (!current_dir)
		return (0);
	dir_entry = readdir(current_dir);
	while (dir_entry && strcmp(cmd, dir_entry->d_name))
		dir_entry = readdir(current_dir);
	if (dir_entry && !ft_strcmp(cmd, dir_entry->d_name))
		return (false_exec(path, cmd), closedir(current_dir), 1);
	closedir(current_dir);
	return (0);
}

int check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		return (i);
	return (-1);
}

int check_is_env_var(char **str)
{
	int	i;
	char	*var;
	char	*new_str;

	if (check_dollar(*str) == -1)
		return (0);
	i = check_dollar(*str);
	var = ft_strdup(getenv(*str + i + 1));
	if (!var)
		return ((void) printf("\33[2K\r"), 0);
	*(str + i) = '\0';
	new_str = ft_strjoin(*str, var);
	free(*str);
	*str = new_str;
	return (1);
}

