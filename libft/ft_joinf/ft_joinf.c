/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:33:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/26 14:53:39 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"

/// @brief Print string with options and variable. 
/// @param *string string to print,
/// @param Any variable to print.
/// @return Return number of char printed and -1 if error occured.
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
	i = 0;
	while (*string)
	{
		while (*string != '%' && *string)
			str[i++] = *string++;
		if (*string == '%')
		{
			string++;
			pass_specifier(*string, args, &str, &i);
		}
		if (*string)
			string++;
	}
	return (va_end(args), str);
}

// TODO check possible memory error
void	pass_specifier(char specifier, va_list args, char **str, int *i)
{
	char	*parse;
	int		j;

	if (specifier == 'c')
		return ((void)(*str[*i++] = va_arg(args, int)));
	if (specifier == 's')
		parse = va_arg(args, char *);
	if (specifier == 'd' || specifier == 'i')
		parse = ft_itoa(va_arg(args, int));
	if (!parse)
		return ;
	j = 0;
	while (parse[j])
		*str[*i++] = parse[j++];
	if (specifier == 'd' || specifier == 'i')
		free(parse);
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
			i += predict_len(str, args_cp);
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
