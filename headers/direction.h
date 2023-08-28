/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:30:19 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/28 22:34:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTION_H
# define DIRECTION_H

// srcs/parsing/direction/input.c:
void	set_input(char *name, t_prompt *prompt);

	// srcs/parsing/direction/heredoc.c:
void	heredoc(int use_env_var, char *eof_name, t_prompt *prompt);
int		create_heredoc_fd(t_prompt *prompt);
int		write_heredoc(t_prompt *p, char *heredoc_name, int use_env_var);

// srcs/parsing/direction/output.c:
void	set_output(t_prompt *prompt);
int		get_last_output_fd(t_arg **args);

// srcs/parsing/direction/direction.c:
void	check_redirection(t_prompt *prompt);
void	reset_stdio_fd(t_prompt *prompt);

#endif
