/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/11 14:49:17 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// TODO signals

struct s_minishell	g_minishell;

struct termios		termios_save;

void	reset_the_terminal(void)
{
	tcsetattr(0, 0, &termios_save );
}

void	handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		write(1, CTRL_C, 3);
		rl_on_new_line();
	//	rl_replace_line("", 0);
		rl_redisplay();
	}
	(void)info;
	(void)context;
}

char *get_mini_prompt(t_garbage *garbage)
{
	char	*prompt;
	
	prompt = ft_joinf(PROMPT, g_minishell.error_value);
	if (!prompt)
		return (MEM_ERR_PROMPT);
	ft_add_garbage(0, &garbage, prompt);
	return (prompt);
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
		g_minishell.error_value = errno;
		s = readline(get_mini_prompt(garbage));
		if (s == NULL)
		{
			printf(EXIT);
			ft_exit(garbage, NULL);
		}
		add_history(s);
		parse(s, garbage);
		free_garbage(garbage);
		garbage = NULL;
		garbage = ft_new_garbage(0, NULL, garbage);
	}
}
