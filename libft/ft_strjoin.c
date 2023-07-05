/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:44:51 by mwubneh           #+#    #+#             */
/*   Updated: 2022/12/10 14:04:26 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	j;
	size_t	i;
	size_t	len_s3;
	char	*s3;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	len_s3 = i + j + 1;
	s3 = malloc(len_s3);
	if (s3 == NULL)
		return (s3);
	ft_bzero(s3, len_s3);
	ft_strlcpy(s3, s1, len_s3);
	ft_strlcpy(s3 + i, s2, len_s3 - i);
	return (s3);
}
