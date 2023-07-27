/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/27 22:33:52 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO signals
// TODO history

struct s_minishell	g_minishell;

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(void)
{
	struct sigaction	sa;
	char				*s;
	t_garbage			*garbage;

	garbage = NULL;
	garbage = ft_new_garbage(0, NULL, garbage);
	g_minishell.garbage = garbage;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
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
