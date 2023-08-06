/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:17:56 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/06 16:27:26 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// srcs/parsing/args/wildcard.c:
void	check_for_wildcard(t_prompt *prompt, char **args, int index,
			t_garbage *garbage);
int		respect_pattern(char *str, char *pattern, char **keys);
void	delete_unwanted_files(char **files, char *pattern, t_garbage *garbage);
int		get_nb_of_files(char *path);
char	**get_files_in_dir(char *path, t_garbage *garbage);

// srcs/parsing/args/args.c:
void	get_args(t_prompt *prompt, char *input, t_garbage *garbage);
void	delete_redirection(char **args);
void	printf_args(char **tab, char *prompt);
void	parse_args(t_prompt *prompt, char **args, t_garbage *garbage);

//srcs/parsing/args/split_args.c:
char	**alloc_tab_args(char const *s, char c, t_garbage *garbage);
char	*get_word_arg(char const *s, char c, int i, t_garbage *garbage);
char	**ft_split_args(t_prompt *prompt, char *s, char c, t_garbage *garbage);

//srcs/parsing/args/tab_utils.c:
void	delete_element_at_index(char **tab, int index);
char	**insert_tab_at_index(char **t1, char **t2, int index,
			t_garbage *garbage);

//srcs/parsing/args/separate_cmd.c:
void	separate_cmd(t_prompt *prompt, char *input, t_garbage *garbage);
int		get_nearer_separator_pos(char *input);
int		is_char_quoted(char *str, int pos);
int		get_separator_pos(char *input, char *sep);