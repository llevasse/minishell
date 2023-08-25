/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:32:26 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/25 22:02:06 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get position of substr if present and -1 if not
int	get_substr_pos(char *str, char *sub_str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strncmp(str + i, sub_str, ft_strlen(sub_str)))
		i++;
	if (!ft_strncmp(str + i, sub_str, ft_strlen(sub_str)))
		return (i);
	return (-1);
}

char	*get_pre_substr(char *str, char *substr, t_minishell *shell)
{
	char	*pre_substr;
	int		substr_pos;

	substr_pos = get_substr_pos(str, substr);
	if (substr_pos == -1)
		return ("");
	str[substr_pos] = 0;
	pre_substr = ft_strdup(str);
	ft_add_garbage(0, &shell->garbage, pre_substr, shell);
	str[substr_pos] = *substr;
	return (pre_substr);
}

char	*get_post_substr(char *str, char *substr, t_minishell *shell)
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
		ft_add_garbage(0, &shell->garbage, post_substr, shell);
	}
	return (post_substr);
}

/// @brief Replace *old_substr in **str by *new_substr.
void	replace_str(char **str, char *old_substr, char *new_substr,
					t_minishell *shell)
{
	char	*new_str;
	char	*pre_substr;
	char	*post_substr;

	if (get_substr_pos(*str, old_substr) == -1)
		return ;
	if (!new_substr)
		new_substr = "";
	pre_substr = get_pre_substr(*str, old_substr, shell);
	post_substr = get_post_substr(*str, old_substr, shell);
	new_str = ft_strjoin(pre_substr, new_substr);
	ft_add_garbage(0, &shell->garbage, new_str, shell);
	new_substr = ft_strjoin(new_str, post_substr);
	ft_add_garbage(0, &shell->garbage, new_substr, shell);
	*str = new_substr;
}
