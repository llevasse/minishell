/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:32:26 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/14 11:33:59 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_pre_substr(char *str, char *substr, t_garbage *garbage)
{
	char	*pre_substr;
	int		substr_pos;

	substr_pos = get_substr_pos(str, substr); 
	if (substr_pos == -1)
		return ("");
//	printf("%d substr pos\n", substr_pos);
	str[substr_pos] = 0;
	pre_substr = ft_strdup(str);
	if (!pre_substr)
		return (ft_exit(garbage), NULL);
	ft_add_garbage(&garbage, ft_new_garbage(pre_substr));
	str[substr_pos] = *substr;
//	printf("'%s' pre substr\n", pre_substr);
	return (pre_substr);
}

char	*get_post_substr(char *str, char *substr, t_garbage *garbage)
{
	char	*post_substr;
	int		substr_pos;

	substr_pos = get_substr_pos(str, substr);
	post_substr = ft_strdup(str + substr_pos + ft_strlen(substr));
	if (!post_substr)
		return (ft_exit(garbage), NULL);
	ft_add_garbage(&garbage, ft_new_garbage(post_substr));
//	printf("'%s' post substr\n", post_substr);
	return (post_substr);
}

/// @brief Replace *old_substr in **str by *new_substr.
void	replace_str(char **str, char *old_substr, char *new_substr, t_garbage *garbage)
{
	char	*new_str;
	char	*pre_substr;
	char	*post_substr;

//	printf("'%s' str\n", *str);
//	printf("('%s' / '%s') old_/new_substr\n", old_substr, new_substr);
	if (!new_substr)
		new_substr = "";
	pre_substr = get_pre_substr(*str, old_substr, garbage);
	post_substr = get_post_substr(*str, old_substr, garbage);
	new_str = ft_strjoin(pre_substr, new_substr);
	free(pre_substr);
	new_substr = NULL;
	if (!new_str)
		return (ft_exit(garbage));
	new_substr = ft_strjoin(new_str, post_substr);
	free(post_substr);
	free(new_str);
	if (!new_substr)
		return (ft_exit(garbage));
	*str = new_substr;
}

