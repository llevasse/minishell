/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:51:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 12:52:06 by llevasse         ###   ########.fr       */
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
	check_cmd(prompt);
	exports = ft_joinf("_=%s",
			prompt->full_args[get_arg_size(prompt->full_args) - 1]);
	ft_add_garbage(1, &shell->at_exit_garbage, exports, shell);
	delete_duplicate_export("_", shell);
	shell->env = insert_at_end(exports, shell->env, shell);
	prompt->exec_fd[0] = -1;
	reset_stdio_fd(prompt);
	prompt = NULL;
}

/// @brief Check if t_prompt is a builtin of a command in PATH
/// @param *cmd Pointer to t_prompt;
void	check_cmd(t_prompt *prompt)
{
	if (!ft_strcmp(prompt->cmd, ""))
	{
		ft_printf(ERR_404, "''");
		return ((void)(errno = 127));
	}
	if (!ft_strcmp(prompt->cmd, "exit") && !prompt->next_cmd)
		return (ft_exit(prompt->shell, prompt->args));
	exec(prompt);
	if (errno == 127)
		prompt->shell->error_value = 127;
}

//pos_sep[0] == pos_sep
//pos_sep[1] == pos_space
void	get_cmd_wo_space(char **input, int pos_sep[2], \
		t_prompt *prompt, t_minishell *shell)
{
	if (pos_sep[0] != -1 && ((pos_sep[1] != -1 && \
		pos_sep[0] < pos_sep[1]) || (pos_sep[1] == -1)))
		*input = NULL;
	if (get_char_pos(prompt->cmd, '|') != -1)
		prompt->cmd[get_char_pos(prompt->cmd, '|')] = 0;
	if (get_char_pos(prompt->cmd, '>') != -1)
	{
		*input = ft_strdup(prompt->cmd + get_char_pos(prompt->cmd, '>'));
		ft_add_garbage(0, &shell->garbage, *input, shell);
		prompt->cmd[get_char_pos(prompt->cmd, '>')] = 0;
	}
	if (get_char_pos(prompt->cmd, '<') != -1)
	{
		*input = ft_strdup(prompt->cmd + get_char_pos(prompt->cmd, '<'));
		ft_add_garbage(0, &shell->garbage, *input, shell);
		prompt->cmd[get_char_pos(prompt->cmd, '<')] = 0;
	}
}

//pos_sep[0] == pos_sep
//pos_sep[1] == pos_space
void	get_cmd_strsep(char **input, t_prompt *prompt, t_minishell *shell)
{
	int	pos_sep[2];
	int	i;

	i = skip_char(*input, ' ', 0);
	if (*input[i] == '|')
		return ((void)(ft_putstr_fd(UNEXPEC_PIPE, 2), prompt->cmd = NULL));
	pos_sep[0] = get_nearer_separator_pos(*input);
	pos_sep[1] = get_char_pos(*input, ' ');
	if (pos_sep[0] != -1 && ((pos_sep[1] != -1 && \
		pos_sep[0] < pos_sep[1]) || (pos_sep[1] == -1)))
		ft_add_prompt(&prompt, init_prompt((*input) + pos_sep[0] + 1, \
			shell->garbage, prompt->shell));
	prompt->cmd = ft_strsep(input, " ");
	get_cmd_wo_space(input, pos_sep, prompt, shell);
	check_is_env_var(prompt, &prompt->cmd, shell);
}

void	get_cmd(char **input, t_prompt *prompt, t_minishell *shell)
{
	int	i;

	i = skip_char(*input, ' ', 0);
	if ((*input)[i] == '"')
	{
		if (get_char_occurance(*input, '"') % 2 != 0)
			no_end_quote(input, '"', W_DQUOTE, prompt->shell);
		prompt->cmd = get_quoted_str(*input, '"', 1, prompt);
		(*input) += 2 + get_char_pos((*input) + 1, '"');
	}
	else if ((*input)[i] == 39)
	{
		if (get_char_occurance(*input, 39) % 2 != 0)
			no_end_quote(input, 39, W_QUOTE, prompt->shell);
		prompt->cmd = get_quoted_str(*input, 39, 0, prompt);
		(*input) += 2 + get_char_pos((*input) + 1, 39);
	}
	else
		get_cmd_strsep(input, prompt, shell);
	if (!prompt->cmd || prompt->cmd[0] == 0)
		return ;
	if (!is_builtin(prompt->cmd))
		prompt->cmd = get_cmd_w_path(prompt, shell);
}
