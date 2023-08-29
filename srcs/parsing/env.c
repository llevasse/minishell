/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/29 15:34:49 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env, char *search, t_minishell *shell)
{
	int		i;
	char	*search_e;
	char	*res;

	i = 0;
	search_e = ft_joinf("%s=", search);
	ft_add_garbage(0, &shell->garbage, search_e, shell);
	while (env[i] && ft_strncmp(search_e, env[i], ft_strlen(search_e)))
		i++;
	if (!env[i])
		return (NULL);
	res = env[i];
	return (res + ft_strlen(search_e));
}

/// @brief Get path of cmd in env.
/// @return If the path of cmd is found it will be returned,
/// else NULL is returned.
char	*get_cmd_w_path(t_prompt *prompt, t_minishell *shell)
{
	char	*path;
	char	*temp;
	int		has_exec;

	has_exec = 0;
	if (prompt->cmd[0] == '.')
		return (prompt->cmd);
	if (!ft_getenv(prompt->environ, "PATH", shell))
		return ((void)printf(ERR_404, prompt->cmd), NULL);
	path = ft_strdup(ft_getenv(prompt->environ, "PATH", shell));
	ft_add_garbage(0, &shell->garbage, path, shell);
	while (*path && !has_exec)
	{
		temp = ft_strsep(&path, ":");
		has_exec = check_present_in_path(prompt, temp);
	}
	if (prompt->cmd[0] == 0)
		prompt->cmd = "''";
	if (!has_exec)
		return ((void)(printf(ERR_404, prompt->cmd), errno = 127), NULL);
	else if (!has_exec && prompt->cmd[0] == '.')
		path = ft_joinf("%s/%s", get_pwd(shell), prompt->cmd);
	else
		path = ft_joinf("%s/%s", temp, prompt->cmd);
	ft_add_garbage(0, &shell->garbage, path, shell);
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
char	*get_env_var_name(char *str, t_minishell *shell)
{
	int		i;
	int		j;
	char	*var_name;

	i = get_char_pos(str, '$');
	i++;
	j = 0;
	while (str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '?') && \
			!ft_isspace(str[i + j]))
		j++;
	var_name = malloc((j + 2) * sizeof(char));
	ft_add_garbage(0, &shell->garbage, var_name, shell);
	ft_strlcpy(var_name, str + (i - 1), j + 2);
	return (var_name);
}
