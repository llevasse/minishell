/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:13:11 by mwubneh           #+#    #+#             */
/*   Updated: 2022/11/26 05:12:51 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char	*s, int c)
{
	char	*scpy;

	scpy = (char *) s;
	while (*scpy != '\0' && *scpy != (char)c)
		scpy++;
	if (*scpy == (char)c)
		return (scpy);
	else
		return (0);
}
