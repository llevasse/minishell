/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:24:48 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/17 22:13:26 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

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

void	exec_builtin(t_prompt *prompt, t_garbage *garbage)
{
	if (!ft_strcmp(prompt->full_args[0], "cd"))
		ft_cd(prompt);
	else if (!ft_strcmp(prompt->full_args[0], "echo"))
		ft_echo(prompt);
	else if (!ft_strcmp(prompt->full_args[0], "env"))
		ft_env();
	else if (!ft_strcmp(prompt->full_args[0], "export"))
		ft_export(prompt);
	else if (!ft_strcmp(prompt->full_args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(prompt->full_args[0], "unset"))
		ft_unset(prompt);
	else if (!ft_strcmp(prompt->full_args[0], "exit"))
		ft_exit(garbage, prompt->args);
	free_garbage(garbage);
	free_garbage(g_minishell.at_exit_garbage);
	exit(errno);
}

void	exec_builtin_main_thread(t_prompt *prompt)
{
	if (!ft_strcmp(prompt->full_args[0], "export") && prompt->export_args)
		ft_export(prompt);
	if (!ft_strcmp(prompt->full_args[0], "unset") && prompt->args)
		ft_unset(prompt);
}
