/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:55:18 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/19 12:20:03 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:24:48 by llevasse          #+#    #+#             */
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
	char	*current_pwd;

	current_pwd = get_pwd(garbage);
	close(prompt->tmp_fd);
	if (!ft_strcmp(prompt->full_args[0], "cd"))
		ft_cd(prompt, garbage);
	else if (!ft_strcmp(prompt->full_args[0], "echo"))
		ft_echo(prompt);
	else if (!ft_strcmp(prompt->full_args[0], "env"))
		ft_env();
	else if (!ft_strcmp(prompt->full_args[0], "export"))
		ft_export(prompt);
	else if (!ft_strcmp(prompt->full_args[0], "pwd"))
		ft_pwd(prompt, garbage);
	else if (!ft_strcmp(prompt->full_args[0], "unset"))
		ft_unset(prompt);
//	else if (!ft_strcmp(prompt->full_args[0], "exit"))
//		ft_exit(garbage, prompt->args);
	close(1);
	free_garbage(garbage);
	free_garbage(g_minishell.at_exit_garbage);
	exit(errno);
}

int	exec_builtin_main_thread(t_prompt *prompt, t_garbage *garbage)
{
	if (!ft_strcmp(prompt->full_args[0], "export") && prompt->export_args)
	{
		ft_export(prompt);
		return (1);
	}
	if (!ft_strcmp(prompt->full_args[0], "unset") && prompt->args)
	{
		ft_unset(prompt);
		return (1);
	}
	if (!ft_strcmp(prompt->full_args[0], "cd"))
	{
		ft_cd(prompt, garbage);
		return (1);
	}
	else
		return (0);
}
