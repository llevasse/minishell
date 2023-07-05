/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:14:12 by mwubneh           #+#    #+#             */
/*   Updated: 2022/12/17 18:14:16 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (0 <= i)
	{
		if (s[i] == (char) c)
			return (&((char *)s)[i]);
		i--;
	}
	return (NULL);
}
