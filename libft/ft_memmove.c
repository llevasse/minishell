/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:30:00 by mwubneh           #+#    #+#             */
/*   Updated: 2023/01/14 14:20:20 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void	*dst, const void	*src, size_t	n)
{
	void	*start;

	start = dst;
	if (src < start)
		ft_memcpy(start, src, n);
	else if (start < src)
		while (n--)
			*(unsigned char *)start++ = *(unsigned char *)src++;
	return (dst);
}
