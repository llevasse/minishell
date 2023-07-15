/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:29:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/15 14:14:09 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>

typedef struct s_prompt
{
	int				d_quotes;
	int				quotes;
	char			*cmd;
	char			**args;
	struct s_prompt	*input_cmd;
	struct s_prompt	*output_cmd;
}	t_prompt;

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

// SRCS/PARSE //

// parse.c
void		parse(char *input, t_garbage *garbage);
t_prompt	*init_prompt(char *input, t_garbage *garbage);
void		check_cmd(t_prompt *prompt, t_garbage *garbage);
int			check_builtin(t_prompt *prompt, t_garbage *garbage);

// ft_strsep.c 
char		*ft_strsep(char **p_str, const char *delim);

// args.c
void		get_args(t_prompt *prompt, char *input, t_garbage *garbage);
void		parse_args(t_prompt *prompt, char **args, t_garbage *garbage);
char		**alloc_tab_args(char const *s, char c, t_garbage *garbage);
char		*get_word_arg(char const *s, char c, int i, t_garbage *garbage);
char		**ft_split_args(t_prompt *prompt, char *s, char c,
				t_garbage *garbage);

// env.c
int			check_cmd_in_env(t_prompt *prompt, t_garbage *garbage);
int			check_present_in_path(t_prompt *prompt, char *path);
int			check_is_env_var(char **str, t_garbage *garbage);
int			get_char_pos(char *str, char c);
char		*get_env_var_name(char *str, t_garbage *garbage);

// garbage_collector.c
void		free_garbage(t_garbage *garbage);
t_garbage	*ft_new_garbage(void	*address, t_garbage *garbage);
void		ft_add_garbage(t_garbage **lst, void *address);

// quotes.c
int			check_quotes(t_prompt *prompt, char **str, t_garbage *garbage);
void		no_end_quote(char **str, char quote, char *to_print,
				t_garbage *garbage);
void		pass_double_quotes(t_prompt *prompt, char **str,
				t_garbage *garbage);
void		pass_single_quotes(t_prompt *prompt, char **str,
				t_garbage *garbage);
char		*get_quoted_str(char *str, char quote, int env_var,
				t_garbage *garbage);

// replace_str.c
void		replace_str(char **str, char *old_substr, char *new_substr,
				t_garbage *garbage);
int			get_substr_pos(char *str, char *sub_str);

// SRCS/EXEC //
void		false_exec(char *path, t_prompt *prompt);

// SRCS/BUILTIN //
void		ft_echo(t_prompt *cmd);
void		ft_env(void);
void		ft_unset(void);
void		ft_exit(t_garbage *garbage);
void		ft_pwd(void);
void		ft_export(void);
void		ft_cd(void);

#endif
