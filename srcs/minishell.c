/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/17 10:25:48 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pipe limit is around 1000

struct s_minishell	g_minishell;

struct termios		termios_save;

void	reset_the_terminal(void)
{
	tcsetattr(0, 0, &termios_save);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		write(1, CTRL_C, 3);
		rl_on_new_line();
	//	rl_replace_line("", 0);
		rl_redisplay();
		exit(1);
	}
	(void)info;
	(void)context;
}

char	*get_mini_prompt(t_garbage *garbage)
{
	char	*prompt;

	prompt = ft_joinf(PROMPT, g_minishell.error_value);
	if (!prompt)
		return (MEM_ERR_PROMPT);
	ft_add_garbage(0, &garbage, prompt);
	return (prompt);
}

void	set_termios(struct termios *termios)
{
	int	rc;

	rc = tcgetattr(0, &termios_save);
	if (rc)
	{
		perror("tcgetattr");
		exit(1);
	}
	rc = atexit(reset_the_terminal);
	if (rc) 
	{
		perror("atexit");
		exit(1);
	}
	*termios = termios_save;
	termios->c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, termios);
	if (rc)
	{
		perror("tcsetattr");
		exit(1);
	}
}

char	**get_base_env(void)
{
	char **environ;

	environ = malloc(sizeof(char *) * 6);
	if (!environ)
		return (NULL);
	environ[0] = "PATH=/nfs/homes/llevasse/bin:/usr/local/sbin:\
/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:\
/usr/local/games:/snap/bin";
	environ[1] = "TERM=xterm-256color";
	environ[2] = "PWD=/Users/alphom/Documents/42/Learner/minishell";
	environ[3] = "SHLVL=-1";
	environ[4] = "_=/usr/bin/env";
	environ[5] = NULL;
	return (environ);
}

void	update_shlvl(char **env, t_garbage *garbage)
{
	int		lvl;
	char	*new_lvl;
	int		i;

	lvl = ft_atoi(ft_getenv(env, "SHLVL", garbage));
	lvl++;
	i = 0;
	while (env[i] && ft_strncmp("SHLVL=", env[i], 6))
		i++;
	if (!env[i])
		return ;
	new_lvl = ft_itoa(lvl);
	ft_add_garbage(0, &garbage, new_lvl);
	env[i] = ft_joinf("SHLVL=%s", new_lvl);
	ft_add_garbage(0, &garbage, env[i]);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	char				*s;
	t_garbage			*garbage;
	t_garbage			*garbage_at_exit;
	struct termios		termios_new;

	(void)argc;
	(void)argv;
	if (!envp || !envp[0])
	{
		envp = get_base_env();
		if (!envp)
			exit (errno);
	}
	set_termios(&termios_new);
	garbage = ft_new_garbage(0, NULL);
	garbage_at_exit = ft_new_garbage(0, NULL);
	g_minishell.garbage = garbage;
	g_minishell.at_exit_garbage = garbage_at_exit;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	if (sigaction(SIGINT, &sa, NULL) < 0 || sigaction(SIGQUIT, &sa, NULL) < 0)
		return (1);
	g_minishell.error_value = 0;
	printf(STARTUP);
	update_shlvl(envp, garbage_at_exit);
	while (42)
	{
		g_minishell.error_value = errno;
		errno = 0;
		s = readline(get_mini_prompt(garbage));
		if (s == NULL)
			ft_exit(garbage, NULL);
		add_history(s);
		parse(s, garbage, envp);
		free_garbage(garbage);
		garbage = NULL;
		garbage = ft_new_garbage(0, NULL);
	}
}
