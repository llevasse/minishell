/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/15 14:31:32 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check and apply redirection in input.
/// @param *input String of the prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	check_redirection(char *input, t_prompt *prompt, t_garbage *garbage)
{
	int		i;
	char	*cut_section;

	i = 0;
	while (prompt->args[i])
	{
		if (!ft_strcmp(prompt->args[i], "<") && \
				ft_strcmp(prompt->args[i], "<<"))
			set_input(prompt->args[i + 1], prompt, garbage);
		else if (!ft_strcmp(prompt->args[i], "<<"))
			heredoc(input, prompt->args[i + 1], prompt, garbage);
		else if (!ft_strcmp(prompt->args[i], ">"))
			set_output(prompt);
		i++;
		cut_section = get_cut_section(input, garbage);
		input += ft_strlen(cut_section);
	}
	if (prompt->heredoc_fd[0] != -1)
	{
		close(prompt->heredoc_fd[1]);
		if (prompt->cmd)
			dup2(prompt->heredoc_fd[0], STDIN_FILENO);
	}
	delete_redirection(prompt->args);
}
// ALWAYS CLOSE PIPE WRITE-END BEFORE DUP2

/// @brief Get a duplicate of the nearest section from the begining of
/// *input calling a redirection.
/// @param *input Prompt input,
/// @param *garbage Pointer to garbage collector.
/// @return Return the redirection call as str.
char	*get_cut_section(char *input, t_garbage *garbage)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup(input);
	ft_add_garbage(0, &garbage, str);
	while (str[i] && (ft_is_in_str("<>|", str[i]) || ft_isspace(str[i])))
		i++;
	while (str[i] && (!ft_isspace(str[i]) && !ft_is_in_str("<>|", str[i])))
		i++;
	str[i] = '\0';
	return (str);
}

/// @brief Reset STDIN and STDOUT to their original fds and close heredoc_fd.
/// @param *prompt Pointer to prompt struct.
void	reset_stdio_fd(t_prompt *prompt)
{
	if (prompt->heredoc_fd[0] != -1)
	{
		close(prompt->heredoc_fd[0]);
		prompt->heredoc_fd[0] = -1;
	}
	if (prompt->write_fd != -1)
		close(prompt->write_fd);
	prompt->write_fd = -1;
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

void	delete_redirection(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((!ft_strcmp(args[i], ">") && ft_strlen(args[i]) == 1) || \
		(!ft_strcmp(args[i], "<") && ft_strlen(args[i]) == 1) || \
		(!ft_strcmp(args[i], ">>") && ft_strlen(args[i]) == 2) || \
		(!ft_strcmp(args[i], "<<") && ft_strlen(args[i]) == 2))
		{
			if (args[i + 1])
			{
				delete_element_at_index(args, i);
				delete_element_at_index(args, i);
			}
			else
				delete_element_at_index(args, i);
		}
		else if (!ft_strncmp(args[i], "<<", 2) || \
		!ft_strncmp(args[i], "<", 1) || \
		!ft_strncmp(args[i], ">>", 2) || !ft_strncmp(args[i], ">", 1))
			delete_element_at_index(args, i);
		else
			i++;
	}
}
