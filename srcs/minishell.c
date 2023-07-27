/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/27 21:26:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO signals
// TODO history

void	handle_sigint(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	if (sig == SIGINT)
		rl_redisplay();
//	rl_replace_line("minishell >>", 1);
}

int	main(void)
{
	char		*s;
	t_garbage	*garbage;

	garbage = NULL;
	garbage = ft_new_garbage(0, NULL, garbage);
	signal(SIGINT, handle_sigint);
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
