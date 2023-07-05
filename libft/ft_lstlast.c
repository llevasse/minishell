/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:09:27 by mwubneh           #+#    #+#             */
/*   Updated: 2023/01/12 21:22:16 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list	*lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
