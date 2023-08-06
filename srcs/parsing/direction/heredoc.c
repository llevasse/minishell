/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/06 09:58:24 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO replace heredoc file with fd :0

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
	int		j;

	i = get_char_pos(input, '<');
	j = i;
	while (input[i] == '<' || ft_isspace(input[i]))
		i++;
	eof_name = ft_strdup(input + i);
	ft_add_garbage(0, &garbage, eof_name);
	cut_section = get_cut_section(input + j, garbage);
	i = 0;
	while (ft_isspace(eof_name[i]))
		i++;
	eof_name += i;
	if (*eof_name == '"' || *eof_name == 39)
	{
		eof_name = get_quoted_str(eof_name, *eof_name, 1, garbage);
		write_heredoc(prompt, &eof_name, garbage, 0);
	}
	else
	{
		eof_name = ft_strsep(&eof_name, " ");
		write_heredoc(prompt, &eof_name, garbage, 1);
	}
}

/// @brief Get section in input calling the heredoc.
/// @param *input Prompt input,
/// @param *garbage Pointer to garbage collector.
/// @return Return heredoc call as str.
char	*get_cut_section(char *input, t_garbage *garbage)
{
	char	*str;
	char	*name;
	char	quote[2];
	int		i;

	i = 0;
	str = ft_strdup(input);
	name = NULL;
	ft_add_garbage(0, &garbage, str);
	while (str[i] && (str[i] == '<' || ft_isspace(str[i])))
		i++;
	if (str[i] == '"' || str[i] == 39)
	{
		quote[0] = str[i];
		quote[1] = 0;
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
	return (str);
}

char	*replace_space_in_name(char *str, t_garbage *garbage)
{
	int		i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		i++;
		if (str[i] && ft_isspace(str[i]) && str[i - 1] == '\\')
			i++;
	}
	if (!str[i])
		return (str);
	str = insert_at_index(str, "\\", i, garbage);
	str = replace_space_in_name(str, garbage);
	return (str);
}

/// @brief Create heredoc file and get its fd.
/// @param **heredoc_name Pointer to string of heredoc name,
/// @param *garbage Pointer to garbage collector.
/// @return Return fd of heredoc.
int	create_heredoc_fd(t_prompt *prompt, int pipes[2])
{
	pipe(pipes);
	prompt->old_stdin = dup(0);
	prompt->old_stdout = dup(1);
	prompt->write_fd = pipes[1];
	printf("Current write_fd %d\n", prompt->write_fd);
	if (prompt->write_fd == -1)
	{
		printf("Error in opening heredoc\n");
		return (-1);
	}
	return (0);
}

/// @brief Write readline input in heredoc file.
/// @param **heredoc_name Pointer to string of heredoc name,
/// @param *garbage Pointer to garbage collector,
/// @param use_env_var boolean int, 1 if env var are parsed and 0 if not.
void	write_heredoc(t_prompt *p, char **heredoc_name,
						t_garbage *garbage, int use_env_var)
{
	char	*text;
	char	*prompt;
	char	*delimiter;
	int		pipes[2];

	*heredoc_name =	replace_space_in_name(*heredoc_name, garbage);
	delimiter = ft_strdup(*heredoc_name);
	ft_add_garbage(0, &garbage, delimiter);
	if (create_heredoc_fd(p, pipes) == -1)
		return ;
	prompt = ft_strjoin(delimiter, " >");
	ft_add_garbage(0, &garbage, prompt);
	while (1)
	{
		text = readline(prompt);
		if (!ft_strcmp(text, delimiter))
			break ;
		if (use_env_var)
			check_is_env_var(&text, garbage);
		ft_putendl_fd(text, p->write_fd);
		free(text);
		text = NULL;
	}
	free(text);
	text = NULL;
//	close(0);
//	close(1);
	dup2(pipes[0], STDIN_FILENO);
//	close(pipes[1]);
//	close(pipes[0]);
}
