/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:10:31 by mwubneh           #+#    #+#             */
/*   Updated: 2022/12/10 14:52:41 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		size;

	size = 0;
	size = ft_strlen(s1);
	str = malloc(size * sizeof(char) + 1);
	if (str == NULL)
		return (str);
	ft_strlcpy(str, s1, size + 1);
	return (str);
}
