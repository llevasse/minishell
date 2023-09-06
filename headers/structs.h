/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:34:32 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/06 09:14:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_sig
{
	struct sigaction	sigint_parent;
	struct sigaction	sigint_child;
	struct sigaction	sigquit_parent;
	struct sigaction	sig_prompt;
	struct sigaction	sig_exit;
}			t_sig;

typedef struct s_minishell
{
	unsigned char		error_value;
	char				**env;
	struct s_sig		sig;
	struct s_garbage	*garbage;
	struct s_garbage	*at_exit_garbage;
}	t_minishell;

typedef struct s_export
{
	char				*key;
	char				*content;
	struct s_export		*next;
}	t_export;

typedef struct s_arg
{
	char				*s;
	int					quote;
	int					joined_quote;
}	t_arg;

typedef struct s_var
{
	char	*var;
	char	*env_var;
	int		i;
}			t_var;

typedef struct s_var_2
{
	t_arg	**res;
	int		i;
	int		word;
	char	*str;
	char	p;
}			t_var_2;

typedef struct heredoc
{
	char	*prompt;
	char	*delimiter;
	int		len;
	int		is_full;
	int		use_env_var;	
	int		status;	
}			t_heredoc;

typedef struct s_prompt
{
	int					lvl;
	int					old_stdout;
	int					old_stdin;
	int					exec_fd[2];
	int					tmp_fd;
	int					has_redir;
	int					has_output;
	int					has_exec;
	int					exec_pid;
	char				*cmd_wo_path;
	char				*cmd;
	char				**environ;
	t_arg				**args;
	t_arg				**full_args;
	t_export			*export_args;
	char				*heredoc_last_input;
	struct s_prompt		*next_cmd;
	struct s_prompt		*prev_cmd;
	struct s_garbage	*garbage;
	struct s_minishell	*shell;
}	t_prompt;

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

t_prompt	*init_prompt(char *input, t_garbage *garbage, \
				t_minishell *shell, int lvl);
void		ft_add_prompt(t_prompt **lst, t_prompt *new);

// garbage_collector.c
void		free_garbage(t_garbage *garbage);
t_garbage	*ft_new_garbage(void *address);
void		ft_add_garbage(int exit, t_garbage **lst, void *addr, t_minishell \
				*shell);

t_export	*ft_new_export(char *key, char *content, t_minishell *shell);
void		ft_add_export(t_export **lst, char *key, char *content,
				t_minishell *shell);

t_arg		*init_arg(t_minishell *shell);
int			get_arg_size(t_arg **tab);
char		**to_char_array(t_arg **args, t_minishell *shell);
#endif
