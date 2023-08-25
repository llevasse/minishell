/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:51:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/25 21:49:52 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *input, t_garbage *garbage, t_minishell *shell)
{
	t_prompt	*prompt;
	char		*exports;

	if (!input || !*input)
		return ;
	while (ft_isspace(*input))
		input++;
	if (!*input)
		return ;
	prompt = init_prompt(input, garbage, shell);
	ft_add_garbage(0, &shell->garbage, prompt, shell);
	if (!prompt->cmd || errno == 12)
		return ;
	check_cmd(prompt, garbage);
	exports = ft_joinf("_=%s",
			prompt->full_args[get_arg_size(prompt->full_args) - 1]);
	ft_add_garbage(1, &shell->at_exit_garbage, exports, shell);
	delete_duplicate_export("_");
	shell->env = insert_at_end(exports,
			shell->env, shell->at_exit_garbage);
	prompt->exec_fd[0] = -1;
	reset_stdio_fd(prompt);
	prompt = NULL;
}

/// @brief Check if t_prompt is a builtin of a command in PATH
/// @param *cmd Pointer to t_prompt;
void	check_cmd(t_prompt *prompt, t_garbage *garbage)
{
	if (!ft_strcmp(prompt->cmd, ""))
	{
		ft_printf(ERR_404, "''");
		return ((void)(errno = 127));
	}
	if (!ft_strcmp(prompt->cmd, "exit") && !prompt->next_cmd)
		return (ft_exit(prompt->shell, prompt->args));
	exec(prompt, garbage);
	if (errno == 127)
		prompt->shell->error_value = 127;
}

void	get_cmd(char **input, t_prompt *prompt, t_garbage *garbage)
{
	if ((*input)[0] == '"')
	{
		if (get_char_occurance(*input, '"') % 2 != 0)
			no_end_quote(input, '"', W_DQUOTE, garbage);
		prompt->cmd = get_quoted_str(*input, '"', 1, prompt);
		(*input) += 2 + get_char_pos((*input) + 1, '"');
	}
	else if ((*input)[0] == 39)
	{
		if (get_char_occurance(*input, 39) % 2 != 0)
			no_end_quote(input, 39, W_QUOTE, garbage);
		prompt->cmd = get_quoted_str(*input, 39, 0, prompt);
		(*input) += 2 + get_char_pos((*input) + 1, 39);
	}
	else
	{
		prompt->cmd = ft_strsep(input, " ");
		check_is_env_var(prompt, &prompt->cmd, garbage);
	}
	if (prompt->cmd[0] == 0)
		return ;
	if (!is_builtin(prompt->cmd))
		prompt->cmd = get_cmd_w_path(prompt, garbage);
}
