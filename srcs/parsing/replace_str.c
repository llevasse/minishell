/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:32:26 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/10 14:02:12 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pre_substr(char *str, char *substr)
{
	char	*pre_substr;
	int		substr_pos;

	substr_pos = get_substr_pos(str, substr); 
	str[substr_pos] = 0;
	pre_substr = ft_strdup(str);
	if (!pre_substr)
		return (NULL);
	str[substr_pos] = *substr;
	return (pre_substr);
}

char	*get_post_substr(char *str, char *substr)
{
	char	*post_substr;
	int		substr_pos;

	substr_pos = get_substr_pos(str, substr);
	post_substr = ft_strdup(str + substr_pos + ft_strlen(substr));
	if (!post_substr)
		return (NULL);
	return (post_substr);
}

/// @brief Replace *old_substr in **str by *new_substr.
void	replace_str(char **str, char *old_substr, char *new_substr)
{
	char	*new_str;
	char	*pre_substr;
	char	*post_substr;

	if (!new_substr)
		new_substr = "";
	pre_substr = get_pre_substr(*str, old_substr);
	if (!pre_substr)
		return ;
	post_substr = get_post_substr(*str, old_substr);
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
	*str = new_substr;
}

