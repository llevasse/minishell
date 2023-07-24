/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/24 08:22:36 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	heredoc(char *input, t_prompt *prompt, t_garbage *garbage)
{
	char	*eof_name;
	char	*cut_section;
	int		i;
	
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
	if (*eof_name == '"' || *eof_name == 39)
	{
		eof_name = get_quoted_str(eof_name, *eof_name, 1, garbage);
		write_heredoc(&eof_name, garbage, 0);
	}
	else
	{
		eof_name = ft_strsep(&eof_name, " ");
		write_heredoc(&eof_name, garbage, 1);
	}
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

char	*replace_space_in_name(char *str, t_garbage *garbage)
{
	int	i;

	i = 0;
	printf("Searching space in |%s|\n", str);
	while (str[i] && !ft_isspace(str[i]))
	{
		printf("Searching '%c'\n", str[i]);
		i++;
	}
	if (!str[i])
		return ((void)printf("No more space found :(\n"), str);
	replace_str(&str, &str[i], "\\ ", garbage);
	printf("Post replace |%s|\n", str);
	replace_space_in_name(str + i + 2, garbage);
	return (str);
}

int		create_heredoc_fd(char **heredoc_name, t_garbage *garbage)
{
	*heredoc_name = ft_strjoin(".", *heredoc_name);
	ft_add_garbage(0, &garbage, *heredoc_name);
	return (open(*heredoc_name, O_RDWR | O_APPEND | O_CREAT, 0666));
}

void	write_heredoc(char **heredoc_name, t_garbage *garbage, int use_env_var)
{
	char	*text;
	char	*prompt;
	int		fd;

	fd = create_heredoc_fd(heredoc_name, garbage);
	printf("Got EOF : %s with fd %d\n", *heredoc_name, fd);
	prompt = ft_strjoin(*heredoc_name + 1, " >");
	ft_add_garbage(0, &garbage, prompt);
	while (1)
	{
		text = readline(prompt);
		if (!ft_strcmp(text, *heredoc_name + 1))
			break ;
		if (use_env_var)
			check_is_env_var(&text, garbage);
		write(fd, text, ft_strlen(text));
		write(fd, "\n", 1);
		free(text);
		text = NULL;
	}
	free(text);
	text = NULL;
	*heredoc_name = replace_space_in_name(*heredoc_name, garbage);
	printf("Pls delete \"%s\"\n", *heredoc_name);
}
