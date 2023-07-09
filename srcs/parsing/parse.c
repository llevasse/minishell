/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:51:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/09 13:51:22 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *input)
{
	t_prompt	*cmd;

	if (!*input)
		return ;
	cmd = init_cmd(input);
	check_cmd(cmd);
	printf("\n");
}

/// @brief Check if t_cmd is a builtin of a command in PATH
/// @param *cmd Pointer to t_cmd;
void	check_cmd(t_prompt *cmd)
{
	int	i;
	
	if (!cmd)
		return ;
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd());	
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo());	
	if (!ft_strcmp(cmd->cmd, "env"))
		return (ft_env());	
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit());	
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export());	
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd());	
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset());
	if (check_cmd_in_env(cmd))
		return ;
	if (check_is_env_var(&cmd->cmd))
		return (check_cmd(cmd));
	printf("%s unknown command with argument(s) ", cmd->cmd);
	i = 0;
	while (cmd->args && cmd->args[i])
		printf("%s ", cmd->args[i++]);
}

/// @brief Allocate memory and assign values to t_cmd.
/// @param *input Inputed string to get command from.
/// @return Return pointer to t_cmd or NULL if something failed.
t_prompt *init_cmd(char *input)
{
	t_prompt	*cmd;

	cmd = malloc(sizeof(struct s_prompt));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd = ft_strsep(&input, " ");
	if (!*input)
		return (cmd);
	get_args(cmd, input);
	return (cmd);
}

/// @brief Get, and assign to t_cmd, args from inputed string.
/// @param *cmd Pointer to t_cmd,
/// @param *input Inputed string to get args from.

void get_args(t_prompt *cmd, char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '|')
		i++;
	if (input[i] == '|')
		input[i - 1] = '\0';
	cmd->args = ft_split(input, ' ');
	if (!cmd->args)
		return (free(cmd));
	input += i;
}

