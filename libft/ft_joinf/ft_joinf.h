/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:39:11 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/03 19:19:50 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_JOINF_H
# define FT_JOINF_H

# include <stdarg.h>
# include "../libft.h"

char	*ft_joinf(char *string, ...);

int		predict_len(const char *str, va_list args);
int		get_size_base_u(unsigned long long n, const char *base);
int		get_size_base(int n, const char *base);
int		get_int_len(int n);
int		get_unsigned_len(unsigned int n);

void	skip_to_spec(const char **str);

#endif
