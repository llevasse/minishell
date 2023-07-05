/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:48:58 by mwubneh           #+#    #+#             */
/*   Updated: 2022/11/26 05:04:33 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	char	*scpy;
	int		i;

	scpy = s;
	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (*scpy)
		f(i++, scpy++);
}
