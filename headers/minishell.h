/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:29:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/24 22:45:47 by llevasse         ###   ########.fr       */
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
# include <termios.h>
# include <errno.h>
# include "structs.h"
# include "args.h"
# include "direction.h"
# include "messages.h"

// SRCS/PARSE //

void		minishell_loop(t_garbage *garbage);
// parse.c
void		parse(char *input, t_garbage *garbage, char **environ);
void		check_cmd(t_prompt *prompt, t_garbage *garbage);
void		get_cmd(char **input, t_prompt *prompt, t_garbage *garbage);

// ft_strsep.c 
char		*ft_strsep(char **p_str, const char *delim);

// env.c
char		*ft_getenv(char **env, char *search, t_garbage *garbage);
char		*get_cmd_w_path(t_prompt *prompt, t_garbage *garbage);
int			check_present_in_path(t_prompt *prompt, char *path);
int			check_is_env_var(t_prompt *prompt, char **str, t_garbage *garbage);
char		*get_env_var_name(char *str, t_garbage *garbage);

// chars.c
int			get_char_pos(char *str, char c);
int			get_char_occurance(char *str, char c);

// export.c
int			export_list_size(t_export *export);
void		get_export_args(t_prompt *prompt, char *input, t_garbage *garbage);
char		**convert_to_tab(t_export *export);

void		sort_tab_alpha(char **tab);
// quotes.c
int			check_quotes(t_prompt *prompt, char **str, t_garbage *garbage);
void		no_end_quote(char **str, char quote, char *to_print,
				t_garbage *garbage);
void		pass_double_quotes(t_prompt *prompt, char **str,
				t_garbage *garbage);
void		pass_single_quotes(t_prompt *prompt, char **str,
				t_garbage *garbage);
char		*get_quoted_str(char *str, char quote, int env_var,
				t_prompt *prompt);

// replace_str.c
void		replace_str(char **str, char *old_substr, char *new_substr,
				t_garbage *garbage);
int			get_substr_pos(char *str, char *sub_str);

// insert_at_index.c
char		*insert_at_index(char *str, char *to_insert,
				int index, t_garbage *garbage);

// SRCS/EXEC //

// exec.c
void		do_close(int *fd);
void		exec(t_prompt *prompt, t_garbage *garbage);
char		**pass_args_exec(char *path, t_prompt *prompt, t_garbage *garbage);
int			get_tab_size(char **tab);
void		print_unknown_cmd(t_prompt *prompt);
int			ft_execute(t_arg **args, int i, int tmp_fd, char **envp);

// exec_utils.c
void		wait_exec(t_prompt *prompt, int value);
void		swap_fd(t_prompt *prompt);
int			exec_child(t_prompt *prompt, int i, t_garbage *garbage);
int			redir(t_prompt *prompt);
int			cmp_exec(t_prompt *prompt, int i);

// SRCS/BUILTIN //
int			is_builtin(char *cmd);
void		exec_builtin(t_prompt *prompt, t_garbage *garbage);
int			exec_builtin_main_thread(t_prompt *prompt, t_garbage *garbage);
void		ft_echo(t_prompt *prompt);
void		ft_env(void);
char		**duplicate_env(void);
void		replace_env(char *var_name, char *new_value);
void		ft_unset(t_prompt *prompt);
void		ft_exit(t_garbage *garbage, t_arg **args);
void		ft_pwd(t_prompt *prompt, t_garbage *garbage);
char		*get_pwd(t_garbage *garbage);
void		ft_export(t_prompt *prompt);
void		delete_duplicate_export(char *key);
void		ft_cd(t_prompt *prompt, t_garbage *garbage);

// terminal.c
void		set_termios(void);
void		reset_termios(void);
void		handler(int sig, siginfo_t *info, void *context);

// set_env.c
char		**get_base_env(void);
void		set_env(char **envp, t_garbage *garbage_at_exit);

#endif
