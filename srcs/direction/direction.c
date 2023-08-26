/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 15:25:38 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check and apply redirection in input.
/// @param *input String of the prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	check_redirection(t_prompt *prompt)
{
	int		i;

	i = 0;
	if (prompt->old_stdout == -1)
		prompt->old_stdout = dup(1);
	while (prompt->args && prompt->args[i])
	{
		if (prompt->args[i + 1] && !ft_strncmp(prompt->args[i]->s, "<", 2) && \
				ft_strncmp(prompt->args[i]->s, "<<", 3))
			set_input(prompt->args[i + 1]->s, prompt);
		else if (prompt->args[i]->quote == 0 && \
				prompt->args[i]->s[0] == '<' && prompt->args[i]->s[1] != '<')
			set_input(prompt->args[i]->s, prompt);
		else if (!prompt->args[i]->quote && \
				!ft_strcmp(prompt->args[i]->s, "<<"))
			heredoc(prompt->args[i + 1]->quote, prompt->args[i + 1]->s, prompt);
		else if (prompt->has_output == 0 && \
				!prompt->args[i]->quote && prompt->args[i]->s[0] == '>')
			set_output(prompt);
		i++;
	}
	delete_redirection(prompt->args);
}
// ALWAYS CLOSE PIPE WRITE-END BEFORE DUP2

/// @brief Reset STDIN and STDOUT to their original fds and close heredoc_fd.
/// @param *prompt Pointer to prompt struct.
void	reset_stdio_fd(t_prompt *prompt)
{
	if (prompt->exec_fd[0] != -1)
	{
		close(prompt->exec_fd[0]);
		prompt->exec_fd[0] = -1;
	}
	if (prompt->old_stdout != -1)
	{
		dup2(prompt->old_stdout, 1);
		close(prompt->old_stdout);
		prompt->old_stdout = -1;
	}
	if (prompt->old_stdin != -1)
	{
		dup2(prompt->old_stdin, 0);
		close(prompt->old_stdin);
		prompt->old_stdin = -1;
	}
}

void	delete_redirection(t_arg **args)
{
	int		i;
	char	*s;

	i = 0;
	while (args && args[i])
	{
		s = args[i]->s;
		if (!ft_strcmp(s, "|"))
			return ;
		if ((!ft_strcmp(s, ">") || !ft_strcmp(s, "<") || \
			!ft_strcmp(s, ">>") || !ft_strcmp(s, "<<")) && !args[i]->quote)
		{
			if (args[i + 1])
				delete_arg_at_index(args, i);
			delete_arg_at_index(args, i);
		}
		else if (args[i]->quote == 0 && (!ft_strncmp(s, "<<", 2) || \
		!ft_strncmp(s, "<", 1) || \
		!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, ">", 1)))
			delete_arg_at_index(args, i);
		else
			i++;
	}
}
