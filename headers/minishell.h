/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:29:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/25 23:37:01 by llevasse         ###   ########.fr       */
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
# include <limits.h>

typedef struct s_export
{
	char				*key;
	char				*content;
	struct s_export		*next;
}	t_export;

typedef struct s_prompt
{
	int					d_quotes;
	int					quotes;
	int					write_fd;
	int					old_stdout;
	int					old_stdin;
	char				*cmd;
	char				**args;
	t_export			*export_args;
	char				*next_cmd;
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
void		delete_element_at_index(char **tab, int index);
char		**alloc_tab_args(char const *s, char c, t_garbage *garbage);
char		*get_word_arg(char const *s, char c, int i, t_garbage *garbage);
char		**ft_split_args(t_prompt *prompt, char *s, char c,
				t_garbage *garbage);

// env.c
int			check_cmd_in_env(t_prompt *prompt, t_garbage *garbage);
int			check_present_in_path(t_prompt *prompt, char *path, t_garbage *garbage);
int			check_is_env_var(char **str, t_garbage *garbage);
char		*get_env_var_name(char *str, t_garbage *garbage);

// chars.c
int			get_char_pos(char *str, char c);
int			get_char_occurance(char *str, char c);

// garbage_collector.c
void		free_garbage(t_garbage *garbage);
t_garbage	*ft_new_garbage(int log, void *address, t_garbage *garbage);
void		ft_add_garbage(int log, t_garbage **lst, void *address);

// export.c
t_export	*ft_new_export(char *key, char *content, t_garbage *garbage);
void		ft_add_export(t_export **lst, char *key, char *content, t_garbage *garbage);
void		get_export_args(t_prompt *prompt, char *input, t_garbage *garbage);

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

// insert_at_index.c
char		*insert_at_index(char *str, char *to_insert, int index, t_garbage *garbage);

// direction.c
void		check_redirection(char *input, t_prompt *prompt,
				t_garbage *garbage);
void		set_output_append(char *input, t_prompt *prompt, t_garbage *garbage);
void		reset_stdio_fd(t_prompt *prompt);

// output.c
void		set_output(char *input, t_prompt *prompt, t_garbage *garbage);
void		multiple_output(char *input, t_prompt *prompt, t_garbage *garbage);

// input.c
void		set_input(char *input, t_prompt *prompt, t_garbage *garbage);
void		multiple_input(char *input_prompt, t_prompt *prompt, t_garbage *garbage);

// heredoc.c
void		heredoc(char *input, t_prompt *prompt, t_garbage *garbage);
int			create_heredoc_fd(t_prompt *prompt, char **heredoc_name, t_garbage *garbage);
void		write_heredoc(t_prompt *p, char **heredoc_name, t_garbage *garbage, int use_env_var);
char		*get_cut_section(char *input, t_garbage *garbage);

// SRCS/EXEC //
void		false_exec(char *path, t_prompt *prompt, t_garbage *garbage);
char		**pass_args_exec(char *path, t_prompt *prompt, t_garbage *garbage);

// SRCS/BUILTIN //
void		ft_echo(t_prompt *prompt);
void		ft_env(void);
void		ft_unset(t_prompt *prompt);
void		ft_exit(t_garbage *garbage);
void		ft_pwd(void);
void		ft_export(t_prompt *prompt);
void		ft_cd(t_prompt *prompt);

#endif
