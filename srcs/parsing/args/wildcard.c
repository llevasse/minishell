/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:41:19 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/01 22:02:13 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_for_wildcard(t_prompt *prompt, char **arg, int index, t_garbage *garbage)
{
	char	*pwd;

	if (get_char_pos(*arg, '*') == -1)
		return ;
	pwd = get_pwd(garbage);
	printf("Pwd : %s\n", pwd);
	(void)arg;
	(void)prompt;
}

//TODO error handling for opendir

int	respect_pattern(char *str, char *pattern)
{
	char	**keys;
	char	*last_key;
	int		i;

	keys = ft_split(pattern, '*');
	ft_add_garbage(0, &garbage, keys);
	i = 0;
	if (*pattern == '*' && ft_strncmp(keys[0], str, ft_strlen(keys[0])))
		return (0);
	while (*str && keys[i])
	{
		if (get_substr_pos(str, keys[i]) == -1)
			return (0);
		str += get_substr_pos(str, keys[i]) + ft_strlen(keys[i]);
		i++;
	}
	last_key = keys[get_tab_size(keys) - 1];
	if (pattern[ft_strlen(pattern)] != '*')
	{
		if (ft_strcmp(pattern + (ft_strlen(pattern) - 
			ft_strlen(last_key)), last_key))
				return (0);
	}
	else if (keys[i] != NULL)
		return (0);
	return (1);
}

void	delete_unwanted_files(char *str)
{
	// str : *str*x*.c*
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
	while ((dir_entry = readdir(current_dir) != NULL)
		i++;
	return (i);
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
	while ((dir_entry = readdir(current_dir) != NULL)
		files[i++] = dir_entry->d_name;
	files[i] = NULL;
	return (files);
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
