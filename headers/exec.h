/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:48:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/29 23:50:44 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// exec.c
void		exec(t_prompt *prompt);
int			get_tab_size(char **tab);
int			ft_execute(t_arg **args, int tmp_fd, t_minishell *shell);

// exec_utils.c
void		wait_exec(t_prompt *prompt, int value);
void		swap_fd(t_prompt *prompt);
int			exec_child(t_prompt *prompt);
int			redir(t_prompt *prompt);

// exec_utils_2.c
void		sig_init(t_prompt *prompt);
void		signal_termios(t_prompt *prompt);
void		sig_mute(t_prompt *prompt);
int			child_exec(t_prompt *prompt);
t_prompt	*next_prompt(t_prompt *prompt);


#endif
