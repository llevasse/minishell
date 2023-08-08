/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/08 22:48:58 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle heredoc in prompt.
/// Create invisible file, write heredoc content in it, and pass it to command.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	heredoc(char *eof_name, t_prompt *prompt, t_garbage *garbage)
{
	if (prompt->heredoc_fd[0] != -1)
	{
		close(prompt->heredoc_fd[0]);
		close(prompt->heredoc_fd[1]);
		prompt->heredoc_fd[0] = -1;
	}
//	if (*eof_name == '"' || *eof_name == 39)
//	{
//		eof_name = get_quoted_str(eof_name, *eof_name, 1, garbage);
//		write_heredoc(prompt, &eof_name, garbage, 0);
//	}
	write_heredoc(prompt, eof_name, garbage, 1);
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
			printf("Error in opening fd\n");
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
void	write_heredoc(t_prompt *p, char *heredoc_name,
						t_garbage *garbage, int use_env_var)
{
	char	*text;
	char	*prompt;
	char	*delimiter;

	delimiter = ft_strdup(heredoc_name);
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
