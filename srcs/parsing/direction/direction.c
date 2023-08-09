/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/08 23:56:02 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO heredoc if passed after input redirection

/// @brief Check and apply redirection in input.
/// @param *input String of the prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	check_redirection(char *input, t_prompt *prompt, t_garbage *garbage)
{
	int		i;

	i = 0;
	while (prompt->args[i])
	{
		if (!ft_strcmp(prompt->args[i], "<") && ft_strcmp(prompt->args[i], "<<"))
			set_input(prompt->args[i + 1], prompt, garbage);
		else if (!ft_strcmp(prompt->args[i], "<<"))
			heredoc(prompt->args[i + 1], prompt, garbage);
		i++;
	}
	if (get_separator_pos(input, ">") != -1)
		set_output(prompt);
	if (prompt->heredoc_fd[0] != -1)
	{
		close(prompt->heredoc_fd[1]);
		if (prompt->cmd)
			dup2(prompt->heredoc_fd[0], STDIN_FILENO);
	}
	delete_redirection(prompt->args);
}
// ALWAYS CLOSE PIPE WRITE-END BEFORE DUP2

/// @brief Get section in input calling the heredoc.
/// @param *input Prompt input,
/// @param *garbage Pointer to garbage collector.
/// @return Return heredoc call as str.
char	*get_cut_section(char *input, t_garbage *garbage)
{
	char	*str;
	char	*name;
	int		i;

	i = 0;
	str = ft_strdup(input);
	name = NULL;
	ft_add_garbage(0, &garbage, str);
	while (str[i] && (ft_is_in_str("<>|", str[i]) || ft_isspace(str[i])))
		i++;
	if (str[i] == '"' || str[i] == 39)
	{
		name = ft_joinf("%c%s%c", str[i],
				get_quoted_str(str + i, str[i], 0, garbage), str[i]);
		ft_add_garbage(0, &garbage, name);
	}
	else
	{
		while (str[i] && (!ft_isspace(str[i]) && !ft_is_in_str("<>|", str[i])))
			i++;
	}
	if (!name)
		return (str);
	str = ft_strjoin(str, name);
	ft_add_garbage(0, &garbage, str);
	return (str);
}

/// @brief Reset fd 1 to stdout.
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
