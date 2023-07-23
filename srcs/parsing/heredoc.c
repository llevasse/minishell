/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/23 21:44:22 by llevasse         ###   ########.fr       */
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
	printf("got %p as EOF_NAME\n", eof_name);
	ft_add_garbage(0, &garbage, eof_name);
	cut_section = get_cut_section(input + (i - 2), garbage);
	printf("Got cut and replace as |%s|\n", cut_section);
	i = 0;
	while (ft_isspace(eof_name[i]))
		i++;
	eof_name += i;
	eof_name = ft_strsep(&eof_name, " ");
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
	ft_add_garbage(0, &garbage, str);
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
	ft_add_garbage(0, &garbage, *heredoc_name);
	return (open(*heredoc_name, O_RDWR | O_APPEND | O_CREAT, 0666));
}

void	write_heredoc(int fd, char *heredoc_name, t_garbage *garbage)
{
	char *text;
	char *prompt;

	prompt = ft_strjoin(heredoc_name, " >");
	ft_add_garbage(0, &garbage, prompt);
	while (1)
	{
		text = readline(prompt);
		if (!ft_strcmp(text, heredoc_name))
			break ;
		check_is_env_var(&text, garbage);
		write(fd, text, ft_strlen(text));
		write(fd, "\n", 1);
		free(text);
		text = NULL;
	}
	free(text);
	text = NULL;
}
