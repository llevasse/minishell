/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:34:32 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/21 14:13:48 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_minishell
{
	unsigned char		error_value;
	char				**env;
	char				**entry_env;
	struct s_garbage	*garbage;
	struct s_garbage	*at_exit_garbage;
	pid_t				current_pid;
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
	int					id;
	struct s_arg		*next;
}	t_arg;

typedef struct s_prompt
{
	int					write_fd;
	int					old_stdout;
	int					old_stdin;
//	int					heredoc_fd[2];
	int					exec_fd[2];
	int					tmp_fd;
	int					exec_pid;
	char				*cmd;
	char				**environ;
	t_arg				**args;
	t_arg				**full_args;
	t_export			*export_args;
	struct s_prompt		*next_cmd;
	struct s_prompt		*prev_cmd;
	struct s_garbage	*garbage;
}	t_prompt;

typedef struct s_garbage
{
	int					at_exit;
	void				*address;
	struct s_garbage	*next;
}	t_garbage;


t_prompt	*init_prompt(char *input, t_garbage *garbage, char **env);
void		ft_add_prompt(t_prompt **lst, t_prompt *new);

// garbage_collector.c
void		free_garbage(t_garbage *garbage);
t_garbage	*ft_new_garbage(int log, void *address);
void		ft_add_garbage(int log, t_garbage **lst, void *address);

t_export	*ft_new_export(char *key, char *content, t_garbage *garbage);
void		ft_add_export(t_export **lst, char *key, char *content,
				t_garbage *garbage);

t_arg		*init_arg(t_garbage *garbage);
int			get_arg_size(t_arg **tab);
char		**to_char_array(t_arg **args, t_garbage *garbage);
#endif
