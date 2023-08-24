/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/24 09:52:05 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_minishell	g_minishell;

char	*get_mini_prompt(t_garbage *garbage)
{
	char	*prompt;

	prompt = ft_joinf(PROMPT, g_minishell.error_value);
	if (!prompt)
		return (MEM_ERR_PROMPT);
	ft_add_garbage(0, &garbage, prompt);
	return (prompt);
}

void	get_input(t_garbage *garbage)
{
	char	*s;

	g_minishell.garbage = garbage;
	g_minishell.error_value = errno;
	errno = 0;
	s = readline(get_mini_prompt(garbage));
	if (s == NULL)
		ft_exit(garbage, NULL);
	add_history(s);
	parse(s, garbage, g_minishell.env);
}

void	minishell_loop(t_garbage *garbage)
{
	while (42)
	{
		get_input(garbage);
		free_garbage(garbage);
		garbage = ft_new_garbage(NULL);
		garbage->next = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	t_garbage			*garbage;
	t_garbage			*garbage_at_exit;

	(void)argc;
	(void)argv;
	set_termios();
	garbage = ft_new_garbage(NULL);
	garbage_at_exit = ft_new_garbage(NULL);
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	if (sigaction(SIGINT, &sa, NULL) < 0 || sigaction(SIGQUIT, &sa, NULL) < 0)
		return (1);
	g_minishell.error_value = 0;
	set_env(envp, garbage_at_exit);
	printf(STARTUP);
	minishell_loop(garbage);
}
