/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:55:18 by mwubneh           #+#    #+#             */
/*   Updated: 2023/09/03 00:31:04 by llevasse         ###   ########.fr       */
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
//	close(p->tmp_fd);
	if (!ft_strcmp(p->cmd, "cd"))
		ft_cd(p);
	else if (!ft_strcmp(p->cmd, "echo"))
		ft_echo(p);
	else if (!ft_strcmp(p->cmd, "env"))
		ft_env(p->shell);
	else if (!ft_strcmp(p->cmd, "export") && !p->export_args)
		print_export(duplicate_env(p->shell), p->shell);
	else if (!ft_strcmp(p->cmd, "pwd"))
		ft_pwd(p);
	else if (!ft_strcmp(p->cmd, "unset"))
		ft_unset(p);
//	close(0);
//	close(1);
//	close(p->old_stdout);
//	free_garbage(p->shell->at_exit_garbage);
//	free_garbage(p->shell->garbage);
//	exit(errno);
}

/// @brief Execute a builtin command.
/// This command is not meant to print anything, and is only used for builtin
/// modifing the environment.
/// @param *prompt prompt struct containing cmd param,
/// @param *garbage pointer to garbage collector.
int	exec_builtin_main_thread(t_prompt *prompt)
{
	if (!ft_strcmp(prompt->full_args[0]->s, "export") && prompt->export_args)
	{
		ft_export(prompt);
		return (1);
	}
	if (!ft_strcmp(prompt->full_args[0]->s, "unset") && prompt->args)
	{
		ft_unset(prompt);
		return (1);
	}
	if (!ft_strcmp(prompt->full_args[0]->s, "cd"))
	{
		ft_cd(prompt);
		return (1);
	}
	else
		return (0);
}
