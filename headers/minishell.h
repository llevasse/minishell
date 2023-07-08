/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:29:40 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/08 19:10:05 by llevasse         ###   ########.fr       */
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

typedef struct s_cmd
{
	int				checked;
	char			*cmd;
	char			**args;
	struct s_cmd	*input_cmd;
	struct s_cmd	*output_cmd;
}	t_cmd;

	// SRCS/PARSE //
char	*ft_strsep(char **p_str, const char *delim);
void	parse(char *input);
t_cmd	*init_cmd(char *input);
void	get_args(t_cmd *cmd, char *input);
void	check_cmd(t_cmd *cmd);
int		check_cmd_in_env(char *cmd);
int		check_present_in_path(char *cmd, char *path);
int		check_is_env_var(char **str);
int		get_char_pos(char *str, char c);
int		check_quotes(t_cmd *cmd);
void	pass_double_quotes(t_cmd *cmd);

	// SRCS/EXEC //
void	false_exec(char *path, char *cmd);

	// SRCS/BUILTIN //
void	ft_echo(void);
void	ft_env(void);
void	ft_unset(void);
void	ft_exit(void);
void	ft_pwd(void);
void	ft_export(void);
void	ft_cd(void);

#endif
