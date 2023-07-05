/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:16:33 by mwubneh           #+#    #+#             */
/*   Updated: 2022/11/26 04:35:35 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s1;
	char	*s2;

	s1 = (char *)s;
	if (s == NULL || f == NULL)
		return (NULL);
	s2 = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (s2 == NULL)
		return (s2);
	s1 = s2;
	while (*s)
	{
		*s2 = f(s2 - s1, *s++);
		s2++;
	}
	*s2 = '\0';
	return (s1);
}
