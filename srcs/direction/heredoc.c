/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/02 14:25:28 by llevasse         ###   ########.fr       */
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
	write_heredoc(prompt, eof_name, !use_env_var);
	if (prompt->tmp_fd != -1)
		dup2(prompt->exec_fd[0], prompt->tmp_fd);
	if (!prompt->next_cmd)
		do_close(&prompt->exec_fd[1]);
	if (prompt->tmp_fd == -1)
		do_close(&prompt->exec_fd[0]);
	prompt->has_redir = 1;
}

void	heredoc_fork(t_prompt *prompt, int i, int value)
{
	prompt->exec_pid = fork();
	if (prompt->exec_pid == 0)
	{
		signal_termios(prompt);
		heredoc(prompt->args[i]->joined_quote, prompt->args[i]->s + 2, \
		prompt);
		free_garbage(prompt->shell->garbage);
		free_garbage(prompt->shell->at_exit_garbage);
		exit(errno);
	}
	sig_mute(prompt);
	waitpid(prompt->exec_pid, &value, WUNTRACED);
	if (WIFSIGNALED(value) && WTERMSIG(value) == SIGINT)
	{
		write(1, "\n", 1);
		errno = 130;
		return ((void)(prompt->has_redir = -1));
	}
	errno = WEXITSTATUS(value);
	dup2(prompt->exec_fd[0], prompt->tmp_fd);
	if (!prompt->next_cmd)
		do_close(&prompt->exec_fd[1]);
	do_close(&prompt->exec_fd[0]);
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
		return ((void)(doc->status = 1), 0);
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
