/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:12:36 by mwubneh           #+#    #+#             */
/*   Updated: 2022/12/17 18:12:39 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	nbr;
	size_t	i;

	sign = 1;
	nbr = 0;
	i = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (ft_isdigit(str[i]) && *str != '\0')
	{
		if (9223372036854775807 <= nbr && sign == 1)
			return (-1);
		else if (9223372036854775807 < nbr && sign == -1)
			return (0);
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nbr);
}
