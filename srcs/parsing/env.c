/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/17 22:46:15 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

char	*ft_getenv(char **env, char *search, t_garbage *garbage)
{
	int		i;
	char	*search_e;
	char	*res;

	i = 0;
	search_e = ft_joinf("%s=", search);
	ft_add_garbage(0, &garbage, search_e);
	while (env[i] && ft_strncmp(search_e, env[i], ft_strlen(search_e)))
		i++;
	if (!env[i])
		return ("");
	res = env[i];
	return (res + ft_strlen(search_e));
}

/// @brief Get path of cmd in env.
/// @return If the path of cmd is found it will be returned,
/// else NULL is returned.
char	*get_cmd_w_path(t_prompt *prompt, t_garbage *garbage)
{
	char	*path;
	char	*temp;
	int		has_exec;

	has_exec = 0;
	if (!ft_getenv(prompt->environ, "PATH", garbage))
		return ((void)printf(ERR_404, prompt->cmd), NULL);
	path = ft_strdup(ft_getenv(prompt->environ, "PATH", garbage));
	ft_add_garbage(0, &garbage, path);
	while (*path && !has_exec)
	{
		temp = ft_strsep(&path, ":");
		has_exec = check_present_in_path(prompt, temp);
	}
	if (!has_exec && prompt->cmd[0] != '.')
		return ((void)printf(ERR_404, prompt->cmd), NULL);
	else if (!has_exec && prompt->cmd[0] == '.')
		path = ft_joinf("%s/%s", get_pwd(garbage), prompt->cmd);
	else
		path = ft_joinf("%s/%s", temp, prompt->cmd);
	ft_add_garbage(0, &garbage, path);
	return (path);
}

/// @brief Check if prompt is a command present in path.
/// @return If cmd is found return 1 else 0.
int	check_present_in_path(t_prompt *prompt, char *path)
{
	DIR				*current_dir;
	int				entry_errno;
	struct dirent	*dir_entry;

	entry_errno = errno;
	current_dir = opendir(path);
	if (!current_dir)
		return ((void)(errno = entry_errno), 0);
	dir_entry = readdir(current_dir);
	while (dir_entry && ft_strcmp(prompt->cmd, dir_entry->d_name))
		dir_entry = readdir(current_dir);
	if (dir_entry && !ft_strcmp(prompt->cmd, dir_entry->d_name))
		return ((void)closedir(current_dir), 1);
	closedir(current_dir);
	return (0);
}

/// @brief get first possible environnement variable int *str
/// @param *str String to search in.
/// @return Env variable name or NULL if error
char	*get_env_var_name(char *str, t_garbage *garbage)
{
	int		i;
	int		j;
	char	*var_name;

	i = get_char_pos(str, '$');
	i++;
	j = 0;
	while (str[i + j] && str[i + j] != '$' && str[i + j] != 39 \
			&& str[i + j] != '"' && !ft_isspace(str[i + j]))
		j++;
	var_name = malloc((j + 2) * sizeof(char));
	ft_add_garbage(0, &garbage, var_name);
	ft_strlcpy(var_name, str + (i - 1), j + 2);
	return (var_name);
}

/// @brief Check if a string contain a env variable.
/// @param **str Pointer to string to check.
/// @return Return 0 if no env variable and otherwise return 1
/// and replace env variable in *str with his content.
int	check_is_env_var(t_prompt *prompt, char **str, t_garbage *garbage)
{
	char	*var;

	if (get_char_pos(*str, '$') == -1)
		return (0);
	if ((*str)[get_char_pos(*str, '$') + 1] == '?')
	{
		var = ft_itoa(g_minishell.error_value);
		ft_add_garbage(0, &garbage, var);
		replace_str(str, "$?", var, garbage);
	}
	while (get_char_pos(*str, '$') >= 0)
	{
		var = get_env_var_name(*str, garbage);
		replace_str(str, var, ft_getenv(prompt->environ, var + 1, garbage),
			garbage);
	}
	return (1);
}
