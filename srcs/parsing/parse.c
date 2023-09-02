/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:51:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/02 23:54:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *input, t_garbage *garbage, t_minishell *shell)
{
	t_prompt	*prompt;
	char		*exports;

	while (input && *input && ft_isspace(*input))
		input++;
	if (!input || !*input)
		return ;
	prompt = init_prompt(input, garbage, shell, 0);
	if (!prompt)
		return ;
	if (!prompt->cmd && !prompt->full_args[0])
	{
		delete_duplicate_export("_", shell);
		shell->env = insert_at_end("_=", shell->env, shell);
		return ;
	}
	check_cmd(prompt);
	exports = ft_joinf("_=%s",
			prompt->full_args[get_arg_size(prompt->full_args) - 1]);
	ft_add_garbage(1, &shell->at_exit_garbage, exports, shell);
	delete_duplicate_export("_", shell);
	shell->env = insert_at_end(exports, shell->env, shell);
	reset_stdio_fd(prompt);
}

/// @brief Check if t_prompt is a builtin of a command in PATH
/// @param *cmd Pointer to t_prompt;
void	check_cmd(t_prompt *prompt)
{
	if (!prompt->cmd && prompt->args)
		return (check_redirection(prompt));
	if (!ft_strcmp(prompt->cmd, ""))
		return ((void)(errno = 127));
	if (!ft_strcmp(prompt->cmd, "exit") && !prompt->next_cmd)
		return (ft_exit(prompt->shell, prompt->args));
	exec(prompt);
	if (errno == 127)
		prompt->shell->error_value = 127;
}
