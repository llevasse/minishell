/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/28 22:35:17 by llevasse         ###   ########.fr       */
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
		do_close(&prompt->exec_fd[0]);
		do_close(&prompt->exec_fd[1]);
	}
	if (!write_heredoc(prompt, eof_name, use_env_var))
		return ((void)(prompt->has_redir = -1));
	if (prompt->tmp_fd != -1)
		dup2(prompt->exec_fd[0], prompt->tmp_fd);
	if (!prompt->next_cmd)
		do_close(&prompt->exec_fd[1]);
	if (prompt->tmp_fd == -1)
		do_close(&prompt->exec_fd[0]);
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

int	check_heredoc(t_prompt *p, t_heredoc *doc)
{
	char	*text;

	text = readline(doc->prompt);
	if (text == NULL)
	{
		text = ft_joinf("%s%s'\n", UNEXPEC_EOF, doc->delimiter);
		ft_add_garbage(0, &p->garbage, text, p->shell);
		write(2, text, ft_strlen(text));
		return ((void)(doc->status = 0), 0);
	}
	if (!ft_strcmp(text, doc->delimiter))
	{
		if (doc->len < 57000)
			ft_putchar_fd(0, p->exec_fd[1]);
		return ((void)(doc->status = 1), 0);
	}
	if (doc->use_env_var)
		check_is_env_var(p, &text, p->shell);
	if (doc->len < 57000)
	{
		doc->len += ft_strlen(text);
		ft_putendl_fd(text, p->exec_fd[1]);
	}
	return (1);
}

/// @brief Write readline input in heredoc pipe.
/// @param *p Pointer to prompt structure,
/// @param *heredoc_name String of heredoc name,
/// @param *garbage Pointer to garbage collector,
/// @param use_env_var boolean int, 1 if env var are parsed and 0 if not.
int	write_heredoc(t_prompt *p, char *heredoc_name, int use_env_var)
{
	t_heredoc	doc;

	doc.delimiter = ft_strdup(heredoc_name);
	ft_add_garbage(0, &p->garbage, doc.delimiter, p->shell);
	if (create_heredoc_fd(p) == -1)
		return (0);
	doc.prompt = ft_strjoin(doc.delimiter, " >");
	ft_add_garbage(0, &p->garbage, doc.prompt, p->shell);
	doc.len = 0;
	doc.is_full = 0;
	doc.use_env_var = use_env_var;
	while (1)
	{
		if (!check_heredoc(p, &doc))
			break ;
		if (!doc.is_full && doc.len > 57000)
		{
			doc.prompt = ft_strjoin("(heredoc full)", doc.prompt);
			ft_add_garbage(0, &p->garbage, doc.prompt, p->shell);
			doc.is_full = 1;
		}
	}
	return (doc.status);
}
