/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 00:28:14 by mwubneh           #+#    #+#             */
/*   Updated: 2023/07/02 16:06:36 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:10:38 by mwubneh           #+#    #+#             */
/*   Updated: 2023/02/18 11:51:56 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_get_line(char *s)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static void	ft_new_buffer(char *buffer, char *temp)
{
	size_t	i;
	size_t	j;

	if (!temp)
		return ;
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	j = -1;
	if (!temp[i])
	{
		while (++j < BUFFER_SIZE + 1 && buffer[j] != '\0')
			buffer[j] = '\0';
		j = BUFFER_SIZE + 1;
	}
	i++;
	while (++j < BUFFER_SIZE + 1)
	{
		if (temp[i])
			buffer[j] = temp[i++];
		else if (!temp[i])
			buffer[j] = '\0';
	}
	free(temp);
}

static char	*ft_read(int fd, char *temp)
{
	char	*s;
	int		rd;

	rd = 1;
	s = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!s)
		return (NULL);
	while (ft_found(temp, '\n') == 0 && rd != 0)
	{
		rd = read(fd, s, BUFFER_SIZE);
		if (rd == 0)
		{
			break ;
		}
		if (rd == -1)
		{
			free(s);
			free(temp);
			return (NULL);
		}
		s[rd] = '\0';
		temp = ft_strjoin(temp, s);
	}
	free(s);
	return (temp);
}

static void	ft_reset_buffer(char	*buffer)
{
	size_t	i;

	i = -1;
	while (++i < BUFFER_SIZE + 1 && buffer[i] != '\0')
		buffer[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*temp;
	char		*line;

	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[0])
	{
		temp = ft_strjoin(temp, buffer);
		if (temp == NULL)
		{
			ft_reset_buffer(buffer);
			return (NULL);
		}
	}
	temp = ft_read(fd, temp);
	if (!temp)
	{
		ft_reset_buffer(buffer);
		return (NULL);
	}
	line = ft_get_line(temp);
	ft_new_buffer(buffer, temp);
	return (line);
}
