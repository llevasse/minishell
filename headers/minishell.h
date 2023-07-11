/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:29:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/11 11:41:55 by mwubneh          ###   ########.fr       */
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

// SRCS/PARSE //
char		*ft_strsep(char **p_str, const char *delim);
void		parse(char *input);
t_prompt	*init_prompt(char *input);
void		get_args(t_prompt *prompt, char *input);
void		check_cmd(t_prompt *prompt);
int			check_cmd_in_env(t_prompt *prompt);
int			check_present_in_path(t_prompt *prompt, char *path);
int			check_is_env_var(char **str);
int			get_char_pos(char *str, char c);
int			get_substr_pos(char *str, char *sub_str);
int			check_quotes(t_prompt *prompt, char **str);
void		no_end_quote(char **str, char quote, char *to_print);
void		pass_double_quotes(t_prompt *prompt, char **str);
void		pass_single_quotes(t_prompt *prompt, char **str);
void		replace_str(char **str, char *old_substr, char *new_substr);
void		parse_args(t_prompt *prompt, char **args);
char		**ft_split_args(t_prompt *prompt, char *s, char c);
char		*get_quoted_str(char *str, char quote, int env_var);

// SRCS/EXEC //
void		false_exec(char *path, t_prompt *prompt);

// SRCS/BUILTIN //
void		ft_echo(t_prompt *cmd);
void		ft_env(void);
void		ft_unset(void);
void		ft_exit(t_prompt *cmd);
void		ft_pwd(void);
void		ft_export(void);
void		ft_cd(void);

#endif
