/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:03 by mwubneh           #+#    #+#             */
/*   Updated: 2022/11/25 12:33:45 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*b, int c, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *)b;
	while (len-- > 0)
		*str++ = (unsigned char)c;
	return (b);
}
