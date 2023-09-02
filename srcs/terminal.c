/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:04:22 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/31 15:36:35 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_prompt;

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

//rl_replace_line("", 0);
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
			g_prompt = 1;
			write(1, "\33[2K\r(130)minishell >>", 22);
			g_prompt = 130;
			rl_replace_line("", 1);
		}
	}
	if (sig == SIGQUIT && info->si_pid == 0)
		write(1, ERR_QUIT, 21);
	if (sig == SIGQUIT)
		errno = 131;
	if (sig == SIGUSR1)
		exit(0);
}

void	do_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}
