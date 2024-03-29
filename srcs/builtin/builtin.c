/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:55:18 by mwubneh           #+#    #+#             */
/*   Updated: 2023/09/03 13:40:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief check if passe char * is the name of a built in command.
/// @param *cmd name to check.
/// @return Return 1 if a match if found and zero if not.
int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

/// @brief Execute a builtin command.
/// @param *prompt prompt struct containing cmd param,
/// @param *garbage pointer to garbage collector.
/// @bug if STDOUT and/or STDIN are not previously set, 
/// it will be problematic.
/// @bug if this command is not launched in a child process, 
/// then the parent process will be stoped.
void	exec_builtin(t_prompt *p)
{
	if (!ft_strcmp(p->cmd, "cd"))
		ft_cd(p);
	else if (!ft_strcmp(p->cmd, "echo"))
		ft_echo(p);
	else if (!ft_strcmp(p->cmd, "env"))
		ft_env(p->shell);
	else if (!ft_strcmp(p->cmd, "export") && !p->export_args)
		print_export(duplicate_env(p->shell), p->shell);
	else if (!ft_strcmp(p->cmd, "export"))
		ft_export(p);
	else if (!ft_strcmp(p->cmd, "pwd"))
		ft_pwd(p);
	else if (!ft_strcmp(p->cmd, "unset"))
		ft_unset(p);
	else if (!p->prev_cmd && !ft_strcmp(p->cmd, "exit"))
		ft_exit(p->shell, p->args);
}
