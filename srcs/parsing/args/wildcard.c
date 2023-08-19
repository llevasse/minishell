/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:41:19 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/19 10:41:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_for_wildcard(t_prompt *prompt, char **args,
			int index, t_garbage *garbage)
{
	char	*pwd;
	char	**new_args;

	if (!args || !args[index])
		return ((void)(prompt->args = args));
	if (get_char_pos(args[index], 42) == -1)
		check_for_wildcard(prompt, args, index + 1, garbage);
	else
	{
		pwd = get_pwd(garbage);
		new_args = get_files_in_dir(pwd, garbage);
		delete_unwanted_files(new_args, args[index], garbage);
		if (new_args[0])
			delete_element_at_index(args, index);
		args = insert_tab_at_index(args, new_args, index, garbage);
		index++;
		while (args[index] && get_char_pos(args[index], 42) == -1)
			index++;
		check_for_wildcard(prompt, args, index, garbage);
	}
}

//TODO error handling for opendir

// fun fact, the asterisc sign value in ascii is 42, 42 is really everything

int	respect_pattern(char *str, char *pattern, char **keys)
{
	char	*last_key;
	int		i;

	i = 0;
	if (pattern[0] != 42 && ft_strncmp(keys[0], str, ft_strlen(keys[0])))
		return (0);
	while (*str && keys[i])
	{
		if (get_substr_pos(str, keys[i++]) == -1)
			return (0);
		str += get_substr_pos(str, keys[i - 1]) + ft_strlen(keys[i - 1]);
	}
	last_key = keys[get_tab_size(keys) - 1];
	if (pattern[ft_strlen(pattern)] != 42)
	{
		if (ft_strncmp(str + (ft_strlen(str) - \
					ft_strlen(last_key)), last_key, ft_strlen(last_key) + 1))
			return (0);
	}
	else if (keys[i] != NULL)
		return (0);
	return (1);
}

void	delete_unwanted_files(char **files, char *pattern, t_garbage *garbage)
{
	int		i;
	char	**keys;

	keys = ft_split(pattern, 42);
	ft_add_garbage(0, &garbage, keys);
	i = 0;
	while (keys[i])
		ft_add_garbage(0, &garbage, keys[i++]);
	i = 0;
	if (get_char_occurance(pattern, 42) == (int)ft_strlen(pattern))
		return ;
	while (files[i])
	{
		if (!respect_pattern(files[i], pattern, keys))
			delete_element_at_index(files, i);
		else
			i++;
	}
}

int	get_nb_of_files(char *path)
{
	DIR				*current_dir;
	struct dirent	*dir_entry;
	int				i;

	current_dir = opendir(path);
	if (!current_dir)
		return (0);
	i = 0;
	dir_entry = readdir(current_dir);
	while (dir_entry != NULL)
	{
		i++;
		dir_entry = readdir(current_dir);
	}
	closedir(current_dir);
	return (i - 2);
}

char	**get_files_in_dir(char *path, t_garbage *garbage)
{
	DIR				*current_dir;
	struct dirent	*dir_entry;
	char			**files;
	int				i;

	files = malloc(sizeof(char *) * (get_nb_of_files(path) + 1));
	ft_add_garbage(0, &garbage, files);
	current_dir = opendir(path);
	if (!current_dir)
		return (0);
	i = 0;
	dir_entry = readdir(current_dir);
	while (dir_entry != NULL)
	{
		if (ft_strcmp(dir_entry->d_name, ".") && \
			ft_strcmp(dir_entry->d_name, ".."))
		{
			files[i] = ft_strdup(dir_entry->d_name);
			files[i + 1] = NULL;
			ft_add_garbage(0, &garbage, files[i++]);
		}
		dir_entry = readdir(current_dir);
	}
	closedir(current_dir);
	return (files);
}
