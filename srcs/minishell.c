/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/28 21:45:53 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO signals
// TODO history

struct s_minishell	g_minishell;

// TODO prevent ctrl+\ to print anything
struct termios		termios_save;

void reset_the_terminal(void)
{
	tcsetattr(0, 0, &termios_save );
}

void	handler(int sig, siginfo_t *info, void *context)
{
	char	delete[2];

	delete[0] = 127;
	delete[1] = 127;
	if (sig == SIGINT)
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		write(1, delete, 2);
	(void)info;
	(void)context;
}

int	main(void)
{
	struct sigaction	sa;
	char				*s;
	t_garbage			*garbage;
	int					 rc;
	struct termios		termios_new;

	rc = tcgetattr(0, &termios_save );
	if (rc) {perror("tcgetattr"); exit(1); }
	rc = atexit(reset_the_terminal);
	if (rc) {perror("atexit"); exit(1); }
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios_new );
	if (rc) {perror("tcsetattr"); exit(1); }
	garbage = NULL;
	garbage = ft_new_garbage(0, NULL, garbage);
	g_minishell.garbage = garbage;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	if (sigaction(SIGINT, &sa, NULL) < 0 || sigaction(SIGQUIT, &sa, NULL) < 0)
		return (1);
	while (42)
	{
		s = readline("minishell >>");
		add_history(s);
		parse(s, garbage);
		free_garbage(garbage);
		garbage = NULL;
		garbage = ft_new_garbage(0, NULL, garbage);
	}
}
