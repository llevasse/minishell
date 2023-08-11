/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:51:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/11 21:59:00 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

void	parse(char *input, t_garbage *garbage)
{
	t_prompt	*prompt;

	if (!input)
		return ;
	if (!*input)
		return ;
	prompt = init_prompt(input, garbage);
	if (!prompt->cmd)
		return ;
	prompt->full_args = get_full_args(prompt, garbage);
	printf_args(prompt->full_args, "Full args :");
	check_cmd(prompt, garbage);
	reset_stdio_fd(prompt);
	if (prompt->next_cmd)
	{
		check_cmd(prompt->next_cmd, garbage);
		reset_stdio_fd(prompt->next_cmd);
	}
}

int	check_builtin(t_prompt *prompt, t_garbage *garbage)
{
	if (!ft_strcmp(prompt->cmd, "cd"))
		return (ft_cd(prompt), 1);
	if (!ft_strcmp(prompt->cmd, "echo"))
		return (ft_echo(prompt), 1);
	if (!ft_strcmp(prompt->cmd, "env"))
		return (ft_env(), 1);
	if (!ft_strcmp(prompt->cmd, "exit"))
		return (ft_exit(garbage, prompt->args), 1);
	if (!ft_strcmp(prompt->cmd, "export"))
		return (ft_export(prompt), 1);
	if (!ft_strcmp(prompt->cmd, "pwd"))
		return (ft_pwd(), 1);
	if (!ft_strcmp(prompt->cmd, "unset"))
		return (ft_unset(prompt), 1);
	return (0);
}

/// @brief Check if t_prompt is a builtin of a command in PATH
/// @param *cmd Pointer to t_prompt;
void	check_cmd(t_prompt *prompt, t_garbage *garbage)
{
	if (!ft_strcmp(prompt->cmd, ""))
	{
		prompt->cmd = "''";
		return ((void)(print_unknown_cmd(prompt), errno = 127));
	}
	if (check_builtin(prompt, garbage))
		return ;
	if (!prompt->d_quotes && !prompt->quotes && \
			check_quotes(prompt, &prompt->cmd, garbage))
		return (check_cmd(prompt, garbage));
//	if (!prompt->quotes && check_is_env_var(&prompt->cmd, garbage))
//		return (check_cmd(prompt, garbage));
	if (check_cmd_in_env(prompt, garbage))
		return ;
	else
		false_exec(get_pwd(garbage), prompt, garbage);
	if (errno == 127)
		g_minishell.error_value = 127;
}

void	get_cmd(char **input, t_prompt *prompt, t_garbage *garbage)
{
	char	*cmd;

	if ((*input)[0] == '"')
	{
		prompt->d_quotes = 1;
		if (get_char_occurance(*input, '"') % 2 != 0)
			no_end_quote(input, '"', W_DQUOTE, garbage);
		cmd = get_quoted_str(*input, '"', 1, garbage);
		(*input) += 2 + get_char_pos((*input) + 1, '"');
	}
	else if ((*input)[0] == 39)
	{
		prompt->quotes = 1;
		if (get_char_occurance(*input, 39) % 2 != 0)
			no_end_quote(input, 39, W_QUOTE, garbage);
		cmd = get_quoted_str(*input, 39, 0, garbage);
		(*input) += 2 + get_char_pos((*input) + 1, 39);
	}
	else
		cmd = ft_strsep(input, " ");
	prompt->cmd = cmd;
}

/// @brief Allocate memory and assign values to t_prompt.
/// @param *input Inputed string to get command from.
/// @return Return pointer to t_prompt or NULL if something failed.
t_prompt	*init_prompt(char *input, t_garbage *garbage)
{
	t_prompt	*prompt;
	size_t		len;

	prompt = malloc(sizeof(struct s_prompt));
	ft_add_garbage(0, &garbage, prompt);
	prompt->write_fd = -1;
	prompt->old_stdout = -1;
	prompt->old_stdin = -1;
	prompt->d_quotes = 0;
	prompt->quotes = 0;
	prompt->args = NULL;
	prompt->export_args = NULL;
	prompt->next_cmd = NULL;
	prompt->heredoc_fd[0] = -1;
	len = ft_strlen(input);
	get_cmd(&input, prompt, garbage);
	if (!*input || len == ft_strlen(prompt->cmd))
		return (prompt);
	get_args(prompt, input, garbage);
	check_redirection(input, prompt, garbage);
	return (prompt);
}

void	ft_add_prompt(t_prompt **lst, t_prompt *new)
{
	t_prompt	*temp;

	if (!new)
		return (ft_exit(g_minishell.garbage, NULL));
	if (*lst)
	{
		temp = *lst;
		while (temp->next_cmd != NULL)
			temp = temp->next_cmd;
		temp->next_cmd = new;
		return ;
	}
	*lst = new;
}
