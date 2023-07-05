/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:01:39 by mwubneh           #+#    #+#             */
/*   Updated: 2023/01/12 21:29:14 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list	**lst, t_list	*new)
{
	if (lst == NULL )
		return ;
	if (*lst == NULL)
		*lst = new;
	else if (new != NULL)
		ft_lstlast(*lst)->next = new;
}
