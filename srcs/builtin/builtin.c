/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:55:18 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/23 10:36:40 by llevasse         ###   ########.fr       */
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
	close(prompt->tmp_fd);
	if (!ft_strcmp(prompt->full_args[0]->s, "cd"))
		ft_cd(prompt, garbage);
	else if (!ft_strcmp(prompt->full_args[0]->s, "echo"))
		ft_echo(prompt);
	else if (!ft_strcmp(prompt->full_args[0]->s, "env"))
		ft_env();
	else if (!ft_strcmp(prompt->full_args[0]->s, "export"))
		ft_export(prompt);
	else if (!ft_strcmp(prompt->full_args[0]->s, "pwd"))
		ft_pwd(prompt, garbage);
	else if (!ft_strcmp(prompt->full_args[0]->s, "unset"))
		ft_unset(prompt);
	reset_stdio_fd(prompt);
	close(0);
	close(1);
	free_garbage(garbage);
	free_garbage(g_minishell.at_exit_garbage);
	exit(errno);
}

int	exec_builtin_main_thread(t_prompt *prompt, t_garbage *garbage)
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
		ft_cd(prompt, garbage);
		return (1);
	}
	else
		return (0);
}
