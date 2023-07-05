/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:59:46 by mwubneh           #+#    #+#             */
/*   Updated: 2022/11/25 23:34:39 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*str, const char *to_find, size_t len)
{
	int	i;

	if (len <= 0)
		return (NULL);
	if (*to_find == '\0')
		return ((char *)str);
	while (0 < len && *str)
	{
		i = 0;
		while (str[i] == to_find[i] && to_find[i])
		{
			if (len - i == 0)
				return (NULL);
			i++;
		}
		if (to_find[i] == '\0')
			return ((char *)str);
		str++;
		len--;
	}
	return (NULL);
}
