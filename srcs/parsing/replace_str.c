/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:32:26 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/09 23:34:13 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Replace *old_substr in **str by *new_substr.
void	replace_str(char **str, char *old_substr, char *new_substr)
{
	char	*new_str;
	char	*pre_substr;
	char	*post_substr;
	int		substr_pos;

	if (!new_substr)
		new_substr = "";
	substr_pos = get_substr_pos(*str, old_substr); 
	pre_substr = malloc(substr_pos * sizeof(char));
	if (!pre_substr)
		return ;
	ft_strlcpy(pre_substr, *str, substr_pos);
	printf("%s str | %s pre substr | ", *str, pre_substr);
	printf("(%s / %s) old_/new_substr | ", old_substr, new_substr);
	post_substr = ft_strdup(*str + substr_pos + ft_strlen(old_substr));
	printf("%s post substr\n", post_substr);
	if (!post_substr)
		return ((void)(free(pre_substr)));
	new_str = ft_strjoin(pre_substr, new_substr);
	free(pre_substr);
	new_substr = NULL;
	if (!new_str)
		return ((void)(free(post_substr)));
	new_substr = ft_strjoin(new_str, post_substr);
	free(post_substr);
	free(new_str);
	if (!new_substr)
		return ;
	*str = new_str;
}

