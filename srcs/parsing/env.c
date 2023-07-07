/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/07 12:12:55 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if cmd in a command present in env.
/// @return If cmd is found return 1 else 0.
int	check_cmd_in_env(char *cmd)
{
	char	*path;
	int	has_exec;

	has_exec = 0;
	path = getenv("PATH");
	while (*path && !has_exec)
		has_exec = check_present_in_path(cmd, ft_strsep(&path, ":"));
	return (has_exec);
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
	if (dir_entry && !strcmp(cmd, dir_entry->d_name))
		return (false_exec(path, cmd), 1);
	return (0);
}

// DIR *opendir(const char *name);
// struct dirent *readdir(DIR *dirp);
