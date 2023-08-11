/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:34:32 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/11 21:47:21 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_minishell
{
	unsigned char		error_value;
	void				*garbage;
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
	int					dquotes;
	int					quotes;
	int					id;
	struct s_arg		*next;
}	t_arg;

typedef struct s_prompt
{
	int					d_quotes;
	int					quotes;
	int					write_fd;
	int					old_stdout;
	int					old_stdin;
	int					heredoc_fd[2];
	char				*cmd;
	char				**args;
	char				**full_args;
	t_export			*export_args;
	struct s_prompt		*next_cmd;
}	t_prompt;

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

#endif
