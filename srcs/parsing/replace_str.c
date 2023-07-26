/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:32:26 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/24 09:44:30 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/// @brief Get position of substr if present and -1 if not
int	get_substr_pos(char *str, char *sub_str)
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
	str[substr_pos] = 0;
	pre_substr = ft_strdup(str);
	if (!pre_substr)
		return (ft_exit(garbage), NULL);
	ft_add_garbage(0, &garbage, pre_substr);
	str[substr_pos] = *substr;
	return (pre_substr);
}

char	*get_post_substr(char *str, char *substr, t_garbage *garbage)
{
	char	*post_substr;
	int		substr_pos;
	int		substr_len;

	substr_pos = get_substr_pos(str, substr);
	substr_len = ft_strlen(substr);
	if (*(str + substr_pos + substr_len) == 0)
		post_substr = "";
	else
	{	
		post_substr = ft_strdup(str + substr_pos + substr_len);
		if (!post_substr)
			return (ft_exit(garbage), NULL);
		ft_add_garbage(0, &garbage, post_substr);
	}
	return (post_substr);
}

/// @brief Replace *old_substr in **str by *new_substr.
void	replace_str(char **str, char *old_substr, char *new_substr,
					t_garbage *garbage)
{
	char	*new_str;
	char	*pre_substr;
	char	*post_substr;

//	printf("Replace_str received |%s|\n", *str);
//	printf("Old substr : |%s|\n", old_substr);
//	printf("New substr : |%s|\n", new_substr);
	if (!new_substr)
		new_substr = "";
	pre_substr = get_pre_substr(*str, old_substr, garbage);
//	printf("Pre substr : |%s|\n", pre_substr);
	post_substr = get_post_substr(*str, old_substr, garbage);
//	printf("Post substr : |%s|\n", post_substr);
	new_str = ft_strjoin(pre_substr, new_substr);
	ft_add_garbage(0, &garbage, new_str);
	new_substr = ft_strjoin(new_str, post_substr);
	ft_add_garbage(0, &garbage, new_substr);
	*str = new_substr;
}
