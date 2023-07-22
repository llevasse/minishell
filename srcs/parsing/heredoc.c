/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/22 21:53:43 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	heredoc(char *input, t_prompt *prompt, t_garbage *garbage)
{
	char	*eof_name;
	char	*cut_section;
	int		i;
	int		fd;
	
	i = get_char_pos(input, '<') + 2;
	eof_name = ft_strdup(input + i);
	cut_section = get_cut_section(input + (i - 2), garbage);
	printf("Got cut and replace as |%s|\n", cut_section);
	i = 0;
	while (ft_isspace(*eof_name))
		eof_name++;
	ft_add_garbage(&garbage, eof_name);
	eof_name = ft_strsep(&eof_name, " ");
	ft_add_garbage(&garbage, eof_name);
	fd = create_heredoc_fd(&eof_name, garbage);
	printf("Got EOF : %s with fd %d\n", eof_name, fd);
	write_heredoc(fd, eof_name + 1, garbage);
	replace_str(&input, cut_section, eof_name, garbage);
	get_args(prompt, input, garbage);
}

char	*get_cut_section(char *input, t_garbage *garbage)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup(input);
	ft_add_garbage(&garbage, str);
	while (str[i] && str[i] == '<')
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && (!ft_isspace(str[i]) || !ft_is_in_str("<>|", str[i])))
		i++;
	if (str[i] != 0)
		str[i] = 0;
	return (str);
}

int		create_heredoc_fd(char **heredoc_name, t_garbage *garbage)
{
	*heredoc_name = ft_strjoin(".", *heredoc_name);
	ft_add_garbage(&garbage, *heredoc_name);
	return (open(*heredoc_name, O_RDWR | O_APPEND | O_CREAT, 0666));
}

void	write_heredoc(int fd, char *heredoc_name, t_garbage *garbage)
{
	char *text;
	char *prompt;

	prompt = ft_strjoin(heredoc_name, " >");
	ft_add_garbage(&garbage, prompt);
	while (1)
	{
		text = readline(prompt);
		if (!ft_strcmp(text, heredoc_name))
			break ;
		write(fd, text, ft_strlen(text));
		write(fd, "\n", 1);
		free(text);
		text = NULL;
	}
	free(text);
	text = NULL;
}
