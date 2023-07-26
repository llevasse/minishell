/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:33:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/26 22:50:58 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"

char	*ft_joinf(char *string, ...)
{
	va_list	args;
	int		i;
	char	*str;

	if (!string)
		return (NULL);
	va_start(args, string);
	str = malloc(sizeof(char) * (predict_full_str_len(string, args) + 1));
	if (!str)
		return (va_end(args), str);
	ft_bzero(str, predict_full_str_len(string, args) + 1);
	i = 0;
	while (*string)
	{
		while (*string != '%' && *string)
			str[i++] = *string++;
		if (*string == '%')
		{
			string++;
			i = pass_specifier(*string, args, &str, i);
		}
		if (*string)
			string++;
	}
	str[i] = 0;
	return (va_end(args), str);
}

// TODO check possible memory error
int	pass_specifier(char specifier, va_list args, char **str, int i)
{
	char	*parse;
	int		j;

	if (specifier == 'c')
	{
		(*str)[i] = (char)va_arg(args, int); 
		return (i + 1);
	}
	if (specifier == 's')
		parse = va_arg(args, char *);
	if (specifier == 'd' || specifier == 'i')
		parse = ft_itoa(va_arg(args, int));
	if (!parse)
		return (i);
	j = -1;
	while (parse[++j])
	{
		if (!parse[j])
			break ;
		(*str)[i + j] = parse[j];
	}
	i += j;
	if (specifier == 'd' || specifier == 'i')
		free(parse);
	return (i);
}

int	predict_full_str_len(char *str, va_list args)
{
	int		i;
	va_list	args_cp;

	i = 0;
	va_copy(args_cp, args);
	while (*str)
	{
		if (*str == '%' && ft_is_in_str("%%csdiuxXp", *(str + 1)))
		{
			i += predict_len(str + 1, args_cp);
			str += 2;
		}
		else
		{
			i++;
			str++;
		}
	}
	return (i);
}
