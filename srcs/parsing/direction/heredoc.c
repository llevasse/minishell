/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/07 23:08:27 by llevasse         ###   ########.fr       */
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
	int		i;

	i = get_char_pos(input, '<');
	while (input[i] == '<' || ft_isspace(input[i]))
		i++;
	eof_name = ft_strdup(input + i);
	ft_add_garbage(0, &garbage, eof_name);
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
int	create_heredoc_fd(t_prompt *prompt)
{
	if (prompt->heredoc_fd[0] == -1)
	{
		if (pipe(prompt->heredoc_fd) == -1)
		{
			printf("Error in opening heredoc\n");
			return (-1);
		}
	}
	if (prompt->old_stdin == -1)
		prompt->old_stdin = dup(0);
	if (prompt->old_stdout == -1)
		prompt->old_stdout = dup(1);
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

	*heredoc_name =	replace_space_in_name(*heredoc_name, garbage);
	delimiter = ft_strdup(*heredoc_name);
	ft_add_garbage(0, &garbage, delimiter);
	if (create_heredoc_fd(p) == -1)
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
		ft_putendl_fd(text, p->heredoc_fd[1]);
		free(text);
		text = NULL;
	}
	free(text);
	text = NULL;
}
