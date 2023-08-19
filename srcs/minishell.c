/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:39:09 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/19 15:45:26 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_minishell	g_minishell;


void	reset_termios()
{
    struct termios term_settings;

    tcgetattr(STDIN_FILENO, &term_settings);
    term_settings.c_lflag |= (ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		write(1, CTRL_C, 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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

void	set_termios()
{
    struct termios term_setting;

    tcgetattr(STDIN_FILENO, &term_setting);
    term_setting.c_lflag&= ~(ICANON);

    term_setting.c_cc[VMIN] = 1;
    term_setting.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &term_setting);
}

char	**get_base_env(void)
{
	char	**environ;
	char	path[PATH_MAX];

	environ = malloc(sizeof(char *) * 4);
	if (!environ)
		return (NULL);
	environ[0] = ft_joinf("PWD=%s", getcwd(path, PATH_MAX));
	environ[1] = "SHLVL=0";
	environ[2] = "OLDPWD";
	environ[3] = NULL;
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

	(void)argc;
	(void)argv;
	set_termios();
	garbage = ft_new_garbage(0, NULL);
	garbage_at_exit = ft_new_garbage(0, NULL);
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	if (sigaction(SIGINT, &sa, NULL) < 0 || sigaction(SIGQUIT, &sa, NULL) < 0)
		return (1);
	g_minishell.error_value = 0;
	if (!envp || !envp[0])
	{
		envp = get_base_env();
		if (!envp || !envp[0])
			exit (errno);
		ft_add_garbage(0, &g_minishell.at_exit_garbage, envp[0]);
	}
	printf(STARTUP);
	update_shlvl(envp, garbage_at_exit);
	g_minishell.entry_env = envp;
	g_minishell.env = envp;
	g_minishell.at_exit_garbage = garbage_at_exit;
	while (42)
	{
		g_minishell.garbage = garbage;
		g_minishell.error_value = errno;
		errno = 0;
		s = readline(get_mini_prompt(garbage));
		if (s == NULL)
			ft_exit(garbage, NULL);
		add_history(s);
		parse(s, garbage, g_minishell.env);
		free_garbage(garbage);
		garbage = ft_new_garbage(0, NULL);
		garbage->next = NULL;
	}
}
