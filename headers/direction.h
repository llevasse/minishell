/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:30:19 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/21 10:52:31 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTION_H
# define DIRECTION_H

// srcs/parsing/direction/input.c:
void	set_input(char *name, t_prompt *prompt);
char	*get_last_input(char **args);
char	*get_input(char *input_prompt, t_garbage *garbage);
void	multiple_input(char *input_prompt, t_prompt *prompt,
			t_garbage *garbage);
void	write_file_to_fd(int fd_to_read, int fd_to_write, t_garbage *garbage);

	// srcs/parsing/direction/heredoc.c:
void	heredoc(char *input, char *eof_name, t_prompt *prompt,
			t_garbage *garbage);
char	*get_cut_section(char *input, t_garbage *garbage);
char	*replace_space_in_name(char *str, t_garbage *garbage);
int		create_heredoc_fd(t_prompt *prompt);
void	write_heredoc(t_prompt *p, char *heredoc_name,
			t_garbage *garbage, int use_env_var);

// srcs/parsing/direction/output.c:
void	set_output(t_prompt *prompt);
int		get_last_output_index(t_arg **args);

// srcs/parsing/direction/direction.c:
void	check_redirection(char *input, t_prompt *prompt, t_garbage *garbage);
void	set_output_append(char *input, t_prompt *prompt, t_garbage *garbage);
void	reset_stdio_fd(t_prompt *prompt);

#endif
