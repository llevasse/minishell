/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:05:12 by mwubneh           #+#    #+#             */
/*   Updated: 2022/11/25 17:33:44 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	unsigned int	a;
	unsigned int	i;

	a = 0;
	i = 0;
	while (dst[a] && a < n)
		a++;
	while (src[i] && a + i < n - 1 && n)
	{
		dst[a + i] = src[i];
		i++;
	}
	if (a < n)
		dst[a + i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (a + i);
}
