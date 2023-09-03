/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:29:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/03 15:10:52 by llevasse         ###   ########.fr       */
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
# include "exec.h"
# include "args.h"
# include "direction.h"
# include "messages.h"

// SRCS/PARSE //

int			minishell_loop(t_minishell *shell, t_garbage *garbage);
// parse.c
void		parse(char *input, t_garbage *garbage, t_minishell *shell);
void		check_cmd(t_prompt *prompt);
void		get_cmd(char **input, t_prompt *prompt, t_minishell *shell);

// ft_strsep.c 
char		*ft_strsep(char **p_str, const char *delim);

// env.c
char		*ft_getenv(char **env, char *search, t_minishell *shell);
char		*get_cmd_w_path(t_prompt *prompt, t_minishell *shell);
int			check_present_in_path(t_prompt *prompt, char *path);
int			check_is_env_var(char **str, t_minishell *shell);
char		*get_env_var_name(char *str, t_minishell *shell);
int			get_env_var_name_len(char *str);

// chars.c
int			get_char_pos(char *str, char c);
int			get_char_occurance(char *str, char c);

// export.c
int			export_list_size(t_export *export);
void		get_export_args(t_prompt *prompt);

void		sort_tab_alpha(char **tab);
// quotes.c
int			check_quotes(t_prompt *prompt, char **str);

void		pass_double_quotes(t_prompt *prompt, char **str);
void		pass_single_quotes(t_prompt *prompt, char **str);
char		*get_quoted_str(char *str, char quote, int env_var,
				t_prompt *prompt);

// replace_str.c
void		replace_str(char **str, char *old_substr, char *new_substr,
				t_minishell *shell);
int			get_substr_pos(char *str, char *sub_str);

// SRCS/EXEC //

void		pre_parse(char **s, t_minishell *shell);

// SRCS/BUILTIN //
int			is_builtin(char *cmd);
void		exec_builtin(t_prompt *prompt);
int			exec_builtin_main_thread(t_prompt *prompt);
void		ft_echo(t_prompt *prompt);
void		ft_env(t_minishell *shell);
char		**duplicate_env(t_minishell *shell);
void		replace_env(char *var_name, char *new_value, t_minishell *shell);
void		ft_unset(t_prompt *prompt);
void		ft_exit(t_minishell *shell, t_arg **args);
void		ft_pwd(t_prompt *prompt);
char		*get_pwd(t_minishell *shell);
void		print_export(char **env, t_minishell *shell);
void		ft_export(t_prompt *prompt);
void		delete_duplicate_export(char *key, t_minishell *shell);
void		ft_cd(t_prompt *prompt);

// terminal.c
void		set_termios(void);
void		reset_termios(void);
void		handler(int sig, siginfo_t *info, void *context);
void		do_close(int *fd);

// set_env.c
char		**get_base_env(void);
void		set_env(char **envp, t_garbage *garbage, t_minishell *shell);

#endif
