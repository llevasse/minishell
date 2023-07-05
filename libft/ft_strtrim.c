/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 02:11:41 by mwubneh           #+#    #+#             */
/*   Updated: 2022/12/10 15:02:59 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1cpy;
	int		i;
	int		j;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL || *set == 0 || *s1 == 0)
		return (ft_strdup(s1));
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	s1 += i;
	j = ft_strlen(s1);
	while (j && ft_strchr(set, s1[j]))
		j--;
	j++;
	s1cpy = malloc(sizeof(char) * (j + 1));
	if (s1cpy == NULL)
		return (NULL);
	ft_strlcpy(s1cpy, s1, j + 1);
	return (s1cpy);
}
