/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/10 13:55:22 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if cmd in a command present in env.
/// @return If cmd is found return 1 else 0.
int	check_cmd_in_env(t_prompt *prompt)
{
	char	*path;
	int		has_exec;
	char	*p_path;

	has_exec = 0;
	path = ft_strdup(getenv("PATH"));
	if (!path)
		return (0);
	p_path = path;
	while (*path && !has_exec)
		has_exec = check_present_in_path(prompt, ft_strsep(&path, ":"));
	return ((void)p_path, has_exec);
}

/// @brief Check if prompt is a command present in path.
/// @return If cmd is found return 1 else 0.
int	check_present_in_path(t_prompt *prompt, char *path)
{
	DIR				*current_dir;
	struct dirent	*dir_entry;

	current_dir = opendir(path);
	if (!current_dir)
		return (0);
	dir_entry = readdir(current_dir);
	while (dir_entry && ft_strcmp(prompt->cmd, dir_entry->d_name))
		dir_entry = readdir(current_dir);
	if (dir_entry && !ft_strcmp(prompt->cmd, dir_entry->d_name))
		return (false_exec(path, prompt), closedir(current_dir), 1);
	closedir(current_dir);
	return (0);
}

/// @brief Check if c is present in *str.
/// @param *str String to check.
/// @param c Character to find
/// @return Return position of c in *str or -1 if none is found.
int	get_char_pos(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

/// @brief get first possible environnement variable int *str
/// @param *str String to search in.
/// @return Env variable name or NULL if error
char	*get_env_var_name(char *str)
{
	int		i;
	int		j;
	char	*var_name;

	i = get_char_pos(str, '$');
	i++;
	j = 0;
	while (str[i + j] && str[i + j] != '$' && str[i + j] != 39 \
			&& str[i + j] != '"')
		j++;
	var_name = malloc((j + 2) * sizeof(char));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str + (i - 1), j + 2);
	return (var_name);
}

/// @brief Get position of substr if present and -1 if not
int		get_substr_pos(char *str, char *sub_str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strncmp(str + i, sub_str, ft_strlen(sub_str)))
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

/// @brief Check if a string contain a env variable.
/// @param **str Pointer to string to check.
/// @return Return 0 if no env variable and otherwise return 1
/// and replace env variable int *str with his content.
int	check_is_env_var(char **str)
{
	char	*var;

	if (get_char_pos(*str, '$') == -1)
		return (0);
//	while (get_char_pos(*str, '$') >= 0)
//	{
		var = get_env_var_name(*str);
		replace_str(str, var, getenv(var + 1));
//	}
	return (1);
}
