/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:02:32 by mwubneh           #+#    #+#             */
/*   Updated: 2022/11/26 04:16:28 by mwubneh          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_word_count(const char *s, char c)
{
	size_t	word_count;

	word_count = 0;
	while (*s)
	{
		if (*s != c)
			word_count++;
		while (*s && *s != c)
			s++;
		if (*s)
			s++;
	}
	return (word_count);
}

static char	**ft_free_result(char **result, size_t i)
{
	while (i--)
		free(result[i]);
	free(result);
	return (NULL);
}

static char const	*skip_c(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

static size_t	get_end(char const *s, char c)
{
	size_t	end;

	end = 0;
	while (s[end] && s[end] != c)
		end++;
	return (end);
}

char	**ft_split(char const *s, char c)
{
	size_t		word_count;
	char		**result;
	size_t		i;
	size_t		end;

	if (s == NULL)
		return (NULL);
	word_count = ft_get_word_count(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		s = skip_c(s, c);
		end = get_end(s, c);
		result[i] = ft_substr(s, 0, end);
		if (result[i] == NULL)
			return (ft_free_result(result, i));
		s += end;
		i++;
	}
	result[i] = NULL;
	return (result);
}
