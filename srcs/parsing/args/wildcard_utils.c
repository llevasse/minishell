/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:42:36 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/24 09:43:18 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_files(t_arg **files, int i,
						struct dirent *dir_entry, t_garbage *garbage)
{
	files[i] = init_arg(garbage);
	files[i]->s = ft_strdup(dir_entry->d_name);
	files[i + 1] = NULL;
	ft_add_garbage(0, &garbage, files[i]->s);
	ft_add_garbage(0, &garbage, files[i]);
}

t_arg	**get_files_in_dir(char *path, t_garbage *garbage)
{
	DIR				*current_dir;
	struct dirent	*dir_entry;
	t_arg			**files;
	int				i;

	i = get_nb_of_files(path);
	if (i <= 0)
		return (NULL);
	files = malloc(sizeof(t_arg *) * (i + 1));
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
			get_files(files, i++, dir_entry, garbage);
		dir_entry = readdir(current_dir);
	}
	closedir(current_dir);
	return (files);
}
