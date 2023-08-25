/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:17:56 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/25 22:46:56 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

// srcs/parsing/args/wildcard.c:
void	check_for_wildcard(t_prompt *prompt, t_arg **args, int index,
			t_minishell *shell);
int		respect_pattern(char *str, char *pattern, char **keys);
void	delete_unwanted_files(t_arg **files, char *pattern, t_minishell *shell);
int		get_nb_of_files(char *path);
t_arg	**get_files_in_dir(char *path, t_minishell *shell);
t_arg	**get_files_in_dir(char *path, t_minishell *shell);

// srcs/parsing/args/args.c:
void	get_args(t_prompt *prompt, char *input, t_minishell *shell);
t_arg	**get_full_args(t_prompt *prompt, t_minishell *shell);
void	delete_redirection(t_arg **args);
void	printf_args(t_arg **tab, char *prompt);
void	parse_args(t_prompt *prompt, t_arg **args, t_minishell *shell);

//srcs/parsing/args/split_args.c:
t_arg	**alloc_tab_args(char const *s, char c, t_minishell *shell);
char	*get_word_arg(char const *s, char c, int i, t_minishell *shell);
t_arg	**ft_split_args(t_prompt *prompt, char *s, char c, t_minishell *shell);
char	*get_split_quote(t_prompt *prompt, char **s, int *i, int index_word);
//srcs/parsing/args/split_args_utils.c:
void	get_arg_not_quoted(t_prompt *prompt, t_var_2 *var, t_minishell *shell);
int		go_get_that_quote(t_prompt *prompt, t_var_2 *var, t_minishell *shell);
void	we_go_forward(t_arg **res, int *word, t_prompt *prompt);
//srcs/parsing/args/tab_utils.c:
void	delete_element_at_index(char **tab, int index);
void	delete_arg_at_index(t_arg **tab, int index);
char	**insert_at_end(char *s, char **tab, t_minishell *shell);
char	**insert_s_at_index(char *s, char **tab, int index, t_minishell *shell);
char	**insert_alpha(char *s, char **tab, t_minishell *shell);
t_arg	**insert_tab_at_index(t_arg **t1, t_arg **t2, int index,
			t_minishell *shell);

//srcs/parsing/args/separate_cmd.c:
void	separate_cmd(t_prompt *prompt, char *input, t_minishell *shell);
int		get_nearer_separator_pos(char *input);
int		is_char_quoted(char *str, int pos);
int		get_separator_pos(char *input, char *sep);

#endif
