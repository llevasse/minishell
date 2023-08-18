/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:29:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/18 21:30:17 by llevasse         ###   ########.fr       */
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

// parse.c
void		parse(char *input, t_garbage *garbage, char **environ);
t_prompt	*init_prompt(char *input, t_garbage *garbage, char **env);
void		ft_add_prompt(t_prompt **lst, t_prompt *new);
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

// garbage_collector.c
void		free_garbage(t_garbage *garbage);
t_garbage	*ft_new_garbage(int log, void *address);
void		ft_add_garbage(int log, t_garbage **lst, void *address);

// export.c
t_export	*ft_new_export(char *key, char *content, t_garbage *garbage);
void		ft_add_export(t_export **lst, char *key, char *content,
				t_garbage *garbage);
int			export_list_size(t_export *export);
void		get_export_args(t_prompt *prompt, char *input, t_garbage *garbage);
char		**convert_to_tab(t_export *export);

void	sort_tab_alpha(char **tab);
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
void		exec(t_prompt *prompt, t_garbage *garbage);
char		**pass_args_exec(char *path, t_prompt *prompt, t_garbage *garbage);
int			get_tab_size(char **tab);
void		print_unknown_cmd(t_prompt *prompt);

// SRCS/BUILTIN //
int			is_builtin(char *cmd);
void		exec_builtin(t_prompt *prompt, t_garbage *garbage);
void		exec_builtin_main_thread(t_prompt *prompt);
void		ft_echo(t_prompt *prompt);
void		ft_env(void);
void		ft_unset(t_prompt *prompt);
void		ft_exit(t_garbage *garbage, char **args);
void		ft_pwd(t_prompt *prompt);
char		*get_pwd(t_garbage *garbage);
void		ft_export(t_prompt *prompt);
void		delete_duplicate_export(char *key);
void		ft_cd(t_prompt *prompt);

#endif
