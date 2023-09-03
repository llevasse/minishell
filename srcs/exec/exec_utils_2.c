/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:59:13 by mwubneh           #+#    #+#             */
/*   Updated: 2023/09/04 00:52:10 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(t_prompt *prompt)
{
	prompt->shell->sig.sigquit_parent.sa_flags = SA_RESTART;
	prompt->shell->sig.sigquit_parent.sa_handler = SIG_IGN;
	sigemptyset(&prompt->shell->sig.sigquit_parent.sa_mask);
	prompt->shell->sig.sigint_parent.sa_flags = SA_RESTART;
	prompt->shell->sig.sigint_parent.sa_handler = SIG_IGN;
	sigemptyset(&prompt->shell->sig.sigint_parent.sa_mask);
	prompt->shell->sig.sigint_child.sa_flags = SA_RESTART;
//	prompt->shell->sig.sigint_child.sa_handler = SIG_DFL;
	prompt->shell->sig.sigint_child.sa_sigaction = &handler;
	sigemptyset(&prompt->shell->sig.sigint_child.sa_mask);
}

void	signal_termios(t_prompt *prompt)
{
	sigaction(SIGINT, &prompt->shell->sig.sigint_child, NULL);
	reset_termios();
}

void	sig_mute(t_prompt *prompt)
{
	sigaction(SIGQUIT, &prompt->shell->sig.sigquit_parent, NULL);
	sigaction(SIGINT, &prompt->shell->sig.sigint_parent, NULL);
}

int	child_exec(t_prompt *prompt)
{
	signal_termios(prompt);
	if (prompt->prev_cmd)
		prompt->tmp_fd = dup(prompt->exec_fd[0]);
	if (is_builtin(prompt->full_args[0]->s))
		exec_builtin(prompt);
	return (ft_execute(prompt->full_args, prompt->tmp_fd, \
				prompt->shell));
}

t_prompt	*next_prompt(t_prompt *prompt)
{
	swap_fd(prompt);
	return (prompt->next_cmd);
}
