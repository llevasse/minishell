/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:58:00 by mwubneh           #+#    #+#             */
/*   Updated: 2023/07/26 23:20:45 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_JOINF_H
# define FT_JOINF_H
# include "../libft.h"

char	*ft_joinf(char *string, ...);
int		predict_len(const char *str, va_list args);
int		get_size_base(int n, const char *base);
int		get_size_base_u(unsigned long long n, const char *base);
int		get_int_len(int n);
int		get_unsigned_len(unsigned int n);

#endif