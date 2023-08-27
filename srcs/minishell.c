/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/27 11:09:08 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_mini_prompt(t_garbage *garbage, t_minishell *shell)
{
	char	*prompt;

	prompt = ft_joinf(PROMPT, shell->error_value);
	if (!prompt)
		return (MEM_ERR_PROMPT);
	ft_add_garbage(0, &garbage, prompt, shell);
	return (prompt);
}

void	get_input(t_garbage *garbage, t_minishell *shell)
{
	char	*s;

	shell->garbage = garbage;
	shell->error_value = errno;
	errno = 0;
	s = readline(get_mini_prompt(garbage, shell));
	if (s == NULL)
		ft_exit(shell, NULL);
	add_history(s);
	parse(s, garbage, shell);
}

int	minishell_loop(t_minishell *shell, t_garbage *garbage)
{
	while (42)
	{
		sigemptyset(&(shell->sa.sa_mask));
		shell->sa.sa_flags = SA_SIGINFO;
		shell->sa.sa_sigaction = &handler;
		if (sigaction(SIGINT, &shell->sa, NULL) < 0 || \
			sigaction(SIGQUIT, &shell->sa, NULL) < 0)
			return (1);
		get_input(garbage, shell);
		free_garbage(garbage);
		garbage = ft_new_garbage(NULL);
		garbage->next = NULL;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	struct s_minishell	minishell;
	t_garbage			*garbage;
	t_garbage			*garbage_at_exit;

	(void)argc;
	(void)argv;
	set_termios();
	garbage = ft_new_garbage(NULL);
	garbage_at_exit = ft_new_garbage(NULL);
	minishell.error_value = 0;
	minishell.garbage = garbage;
	set_env(envp, garbage_at_exit, &minishell);
	printf(STARTUP);
	if (minishell_loop(&minishell, garbage))
		return (1);
}
