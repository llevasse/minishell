/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:10:29 by mwubneh           #+#    #+#             */
/*   Updated: 2022/11/26 00:12:15 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;

	i = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	str = malloc(i);
	if (str == NULL)
		return (str);
	ft_bzero(str, i);
	return (str);
}
