/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:51:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/05 22:55:53 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *input, t_garbage *garbage, t_minishell *shell)
{
	t_prompt	*prompt;

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
}

void	register_last_args(t_prompt *p, t_minishell *shell)
{
	char		*exports;
	int			i;

	i = !!get_arg_size(p->full_args);
	exports = ft_joinf("_=%s",
		p->full_args[get_arg_size(p->full_args) - i]->s);
	ft_add_garbage(1, &shell->at_exit_garbage, exports, shell);
	delete_duplicate_export("_", shell);
	shell->env = insert_at_end(exports, shell->env, shell);
	reset_stdio_fd(p);

}

/// @brief Check if t_prompt is a builtin of a command in PATH
/// @param *cmd Pointer to t_prompt;
void	check_cmd(t_prompt *prompt)
{
	if (!prompt->cmd && prompt->args)
		return ((void)redir(prompt));
	if (!ft_strcmp(prompt->cmd, ""))
		return ((void)(errno = 127));
	if (!ft_strcmp(prompt->cmd, "exit") && !prompt->next_cmd)
		return (ft_exit(prompt->shell, prompt->args));
	exec(prompt);
	if (errno == 127)
		prompt->shell->error_value = 127;
}
