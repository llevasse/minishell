/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 22:31:42 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle heredoc in prompt.
/// @param *input Prompt input,
/// @param *eof_name What was parsed as heredoc 'name' (delimiter'),
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	heredoc(int use_env_var, char *eof_name, t_prompt *prompt)
{
	if (use_env_var == 0)
		use_env_var = 1;
	else
		use_env_var = 0;
	if (prompt->exec_fd[0] != -1)
	{
		close(prompt->exec_fd[0]);
		close(prompt->exec_fd[1]);
		prompt->exec_fd[0] = -1;
	}
	write_heredoc(prompt, eof_name, use_env_var);
	prompt->has_redir = 1;
}

/// @brief Create heredoc pipe.
/// @param *prompt Pointer to prompt structure.
/// @return Return 0 if no problem occurs or -1.
int	create_heredoc_fd(t_prompt *prompt)
{
	if (prompt->exec_fd[0] == -1)
	{
		if (pipe(prompt->exec_fd) == -1)
		{
			write(2, PIPE_ERR, ft_strlen(PIPE_ERR));
			return (-1);
		}
	}
	if (prompt->old_stdin == -1)
		prompt->old_stdin = dup(0);
	if (prompt->old_stdout == -1)
		prompt->old_stdout = dup(1);
	return (0);
}

/// @brief Write readline input in heredoc pipe.
/// @param *p Pointer to prompt structure,
/// @param *heredoc_name String of heredoc name,
/// @param *garbage Pointer to garbage collector,
/// @param use_env_var boolean int, 1 if env var are parsed and 0 if not.
void	write_heredoc(t_prompt *p, char *heredoc_name, int use_env_var)
{
	char	*text;
	char	*prompt;
	char	*delimiter;

	delimiter = ft_strdup(heredoc_name);
	ft_add_garbage(0, &p->garbage, delimiter, p->shell);
	if (create_heredoc_fd(p) == -1)
		return ;
	prompt = ft_strjoin(delimiter, " >");
	ft_add_garbage(0, &p->garbage, prompt, p->shell);
	while (1)
	{
		text = readline(prompt);
		if (!ft_strcmp(text, delimiter))
			break ;
		if (use_env_var)
			check_is_env_var(p, &text, p->shell);
		ft_putendl_fd(text, p->exec_fd[1]);
	}
	dup2(p->exec_fd[0], p->tmp_fd);
	close(p->exec_fd[1]);
}
