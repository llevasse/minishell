/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/24 23:21:53 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/// @brief Handle heredoc in prompt.
/// Create invisible file, write heredoc content in it, and pass it to command.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	heredoc(char *input, t_prompt *prompt, t_garbage *garbage)
{
	char	*eof_name;
	char	*cut_section;
	int		i;
	
	i = get_char_pos(input, '<') + 3;
	eof_name = ft_strdup(input + i);
	printf("got %p as |%s|(EOF_NAME)\n", eof_name, eof_name);
	ft_add_garbage(0, &garbage, eof_name);
	cut_section = get_cut_section(input + (i - 3), garbage);
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
	check_redirection(input, prompt, garbage);
	printf("New input |%s|\n", input);
}

/// @brief Get section in input calling the heredoc.
/// @param *input Prompt input,
/// @param *garbage Pointer to garbage collector.
/// @return Return heredoc call as str.
char	*get_cut_section(char *input, t_garbage *garbage)
{
	char	*str;
	char	*name;
	char	quote[1];
	int		i;

	i = 0;
	str = ft_strdup(input);
	name = NULL;
	ft_add_garbage(0, &garbage, str);
	while (str[i] && str[i] == '<')
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '"' || str[i] == 39)
	{
		quote[0] = str[i];
		name = ft_strjoin(get_quoted_str(str + i, str[i], 0, garbage), quote);
		ft_add_garbage(0, &garbage, name);
		name = ft_strjoin(quote, name);
		ft_add_garbage(0, &garbage, name);
	}
	else
	{
		while (str[i] && (!ft_isspace(str[i]) && !ft_is_in_str("<>|", str[i])))
			i++;
	}
	if (str[i] != 0)
		str[i] = 0;
	if (!str[i] && name)
	{
		str = ft_strjoin(str, name);
		ft_add_garbage(0, &garbage, str);
	}
	printf("Got cut and replace as |%s|\n", str);
	return (str);
}

// TODO replace space of file name with '\ ' to fix some stuff
// ex :
// minishell >> cat << 'j j'
// j j >j j
// minishell >> ls -a
// minishell >> ./ ../ .git/ .j j
// minishell >> rm .j j
// cannot remove '.j' and 'j'
/// @brief Create heredoc file and get its fd.
/// @param **heredoc_name Pointer to string of heredoc name,
/// @param *garbage Pointer to garbage collector.
/// @return Return fd of heredoc.
int		create_heredoc_fd(char **heredoc_name, t_garbage *garbage)
{
	*heredoc_name = ft_strjoin(".", *heredoc_name);
	ft_add_garbage(0, &garbage, *heredoc_name);
	return (open(*heredoc_name, O_RDWR | O_APPEND | O_CREAT, 0666));
}

/// @brief Write readline input in heredoc file.
/// @param **heredoc_name Pointer to string of heredoc name,
/// @param *garbage Pointer to garbage collector,
/// @param use_env_var boolean int, 1 if env var are parsed and 0 if not.
void	write_heredoc(char **heredoc_name, t_garbage *garbage, int use_env_var)
{
	char	*text;
	char	*prompt;
	int		fd;

	fd = create_heredoc_fd(heredoc_name, garbage);
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

	//TODO created equivalent of printf but return the string instead of printing it.
	*heredoc_name = ft_strjoin("\"", *heredoc_name);
	ft_add_garbage(0, &garbage, *heredoc_name);
	*heredoc_name = ft_strjoin(*heredoc_name, "\"");
	ft_add_garbage(0, &garbage, *heredoc_name);
}
