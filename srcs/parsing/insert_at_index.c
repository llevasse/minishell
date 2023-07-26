/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_at_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:37:10 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/26 21:08:43 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Insert char *to_insert at the index of *str.
/// @param *str String needing to add *to_insert into,
/// @param *to_insert String to insert in *str,
/// @param index Index of where in *str to insert *to_insert.
/// @return Return duplicate of *str containing *to_insert.
char	*insert_at_index(char *str, char *to_insert, 
			int index, t_garbage *garbage)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc((ft_strlen(str) + ft_strlen(to_insert) + 1) 
			* sizeof(char));
	ft_add_garbage(0, &garbage, new_str);
	i = 0;
	while (i < index)
	{
		new_str[i] = str[i];
		i++;
	}
	j = 0;
	while (to_insert[j])
		new_str[i++] = to_insert[j++];
	while (str[index])
		new_str[i++] = str[index++];
	new_str[i] = 0;
	return (new_str);
}
