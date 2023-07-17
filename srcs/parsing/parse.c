/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:51:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/17 14:19:53 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *input, t_garbage *garbage)
{
	t_prompt	*prompt;

	if (!*input)
		return ;
	prompt = init_prompt(input, garbage);
	check_cmd(prompt, garbage);
	if (prompt->write_fd == 1)
		reset_stdio_fd(prompt);
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
		return (ft_exit(garbage), 1);
	if (!ft_strcmp(prompt->cmd, "export"))
		return (ft_export(), 1);
	if (!ft_strcmp(prompt->cmd, "pwd"))
		return (ft_pwd(), 1);
	if (!ft_strcmp(prompt->cmd, "unset"))
		return (ft_unset(), 1);
	return (0);
}

/// @brief Check if t_prompt is a builtin of a command in PATH
/// @param *cmd Pointer to t_prompt;
void	check_cmd(t_prompt *prompt, t_garbage *garbage)
{
	int	i;

	if (!prompt)
		return ;
	if (check_builtin(prompt, garbage))
		return ;
	if (!prompt->d_quotes && !prompt->quotes && \
			check_quotes(prompt, &prompt->cmd, garbage))
		return (check_cmd(prompt, garbage));
	if (!prompt->quotes && check_is_env_var(&prompt->cmd, garbage))
		return (check_cmd(prompt, garbage));
	if (check_cmd_in_env(prompt, garbage))
		return ;
	i = 0;
	if (prompt->cmd[0] == '\0')
		prompt->cmd = "''";
	printf("%s unknown command with argument(s) ", prompt->cmd);
	while (prompt->args && prompt->args[i])
		printf("%s ", prompt->args[i++]);
	printf("\n");
}

/// @brief Allocate memory and assign values to t_prompt.
/// @param *input Inputed string to get command from.
/// @return Return pointer to t_prompt or NULL if something failed.
t_prompt	*init_prompt(char *input, t_garbage *garbage)
{
	t_prompt	*prompt;

	prompt = malloc(sizeof(struct s_prompt));
	ft_add_garbage(&garbage, prompt);
	prompt->write_fd = -1;
	prompt->d_quotes = 0;
	prompt->quotes = 0;
	prompt->args = NULL;
	prompt->cmd = ft_strsep(&input, " ");
	if (!*input)
		return (prompt);
	get_args(prompt, input, garbage);
	check_redirection(input, prompt, garbage);
	return (prompt);
}
