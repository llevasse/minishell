/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:32:26 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/26 23:07:37 by mwubneh          ###   ########.fr       */
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
	int		substr_len;

	substr_pos = get_substr_pos(str, substr);
	substr_len = (int)ft_strlen(substr);
	if (substr_pos == -1)
		return ("");
	str[substr_pos] = 0;
	pre_substr = ft_strdup(str);
	ft_add_garbage(0, &garbage, pre_substr);
	str[substr_pos] = *substr;
	(void)substr_len; //silence warning unused value
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

	if (get_substr_pos(*str, old_substr) == -1)
		return ;
	if (!new_substr)
		new_substr = "";
	pre_substr = get_pre_substr(*str, old_substr, garbage);
	post_substr = get_post_substr(*str, old_substr, garbage);
	new_str = ft_strjoin(pre_substr, new_substr);
	ft_add_garbage(0, &garbage, new_str);
	new_substr = ft_strjoin(new_str, post_substr);
	ft_add_garbage(0, &garbage, new_substr);
	*str = new_substr;
}
