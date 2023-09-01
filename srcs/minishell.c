/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:10:20 by mwubneh           #+#    #+#             */
/*   Updated: 2023/09/01 21:43:26 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	g_prompt;

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
	g_prompt = errno;
	errno = 0;
	g_prompt = 0;
	s = readline(get_mini_prompt(garbage, shell));
	if (s == NULL)
		ft_exit(shell, NULL);
	if (s == NULL)
		return ;
	add_history(s);
	shell->error_value = g_prompt;
	errno = g_prompt;
	parse(s, garbage, shell);
}

int	minishell_loop(t_minishell *shell, t_garbage *garbage)
{
	while (42)
	{
		shell->sig.sig_exit.sa_flags = SA_SIGINFO;
		shell->sig.sig_exit.sa_sigaction = &handler;
		sigemptyset(&shell->sig.sig_exit.sa_mask);
		sigemptyset(&(shell->sig.sig_prompt.sa_mask));
		shell->sig.sig_prompt.sa_flags = SA_SIGINFO;
		shell->sig.sig_prompt.sa_sigaction = &handler;
		if (sigaction(SIGINT, &shell->sig.sig_prompt, NULL) < 0 || \
			sigaction(SIGQUIT, &shell->sig.sig_prompt, NULL) < 0 || \
			sigaction(SIGUSR1, &shell->sig.sig_exit, NULL) < 0)
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

	g_prompt = 0;
	(void)argv;
	if (argc != 1)
		return (127);
	set_termios();
	printf(STARTUP);
	garbage = ft_new_garbage(NULL);
	garbage_at_exit = ft_new_garbage(NULL);
	minishell.error_value = 0;
	minishell.garbage = garbage;
	set_env(envp, garbage_at_exit, &minishell);
	if (minishell_loop(&minishell, garbage))
		return (1);
}
