/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 21:54:29 by mwubneh           #+#    #+#             */
/*   Updated: 2022/11/25 14:42:17 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	size_str[12];
	char	*str;
	int		sign;

	sign = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		n *= -1;
		sign *= -1;
	}
	size_str[11] = '\0' ;
	str = size_str + 10;
	while (n > 0)
	{
		*str-- = n % 10 + '0';
		n /= 10;
	}
	if (sign < 0)
		*str-- = '-';
	return (ft_strdup(str + 1));
}
