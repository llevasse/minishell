/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:04:22 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/26 11:58:15 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_termios(void)
{
	struct termios	term_setting;

	tcgetattr(STDIN_FILENO, &term_setting);
	term_setting.c_lflag &= ~(ICANON);
	term_setting.c_lflag &= ~ECHOCTL;
	term_setting.c_cc[VMIN] = 1;
	term_setting.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_setting);
}

void	reset_termios(void)
{
	struct termios	term_settings;

	tcgetattr(STDIN_FILENO, &term_settings);
	term_settings.c_lflag |= (ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
}

//TODO handler specific handler for childprocess (like cmd cat with no args)
//and to print sigquit text when sigquit is sent in child process
void	handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
	{
		if (info->si_pid == 0)
			write(1, "\n", 1);
		if (info->si_pid != 0)
		{
			write(1, CTRL_C, 3);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	if (sig == SIGQUIT && info->si_pid == 0)
		write(1, ERR_QUIT, 19);
}
