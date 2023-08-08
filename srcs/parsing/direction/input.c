/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:52:05 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/08 11:01:46 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle input redirection in prompt.
/// Close stdin fd and assign to input file fd 0, 
/// So that execve will write into it.
/// @param *input Prompt input,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage collector.
void	set_input(t_prompt *prompt, t_garbage *garbage)
{
	char		*name;
	int			fd;
	int			i;

	i = 0;
	while (prompt->args[i])
	{
		if (!ft_strcmp(prompt->args[i], "<") && \
				ft_strcmp(prompt->args[i], "<<"))
			break;
		i++;
	}
	if (prompt->args[i] == NULL)
		return ;
	name = get_last_input(prompt->args);
	if (!name)
		return ((void)printf("Parsing error around <\n"));
	if (prompt->heredoc_fd[0] != -1)
	{
		close(prompt->heredoc_fd[0]);
		close(prompt->heredoc_fd[1]);
		prompt->heredoc_fd[0] = -1;
	}
	if (create_heredoc_fd(prompt) == -1)
		return ;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return ((void)(printf("Error in opening file\n"), prompt->cmd = NULL));
	write_file_to_fd(fd, prompt->heredoc_fd[1], garbage);
}

void	write_file_to_fd(int fd_to_read, int fd_to_write, t_garbage *garbage)
{
	char	*str;

	str = get_next_line(fd_to_read);
	while (str)
	{	
		ft_add_garbage(0, &garbage, str);
		ft_putstr_fd(str, fd_to_write);
		str = get_next_line(fd_to_read);
	}
	close(fd_to_read);
}

char	*get_last_input(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (args[i])
	{
		if (!ft_strcmp("<", args[i]))
			j = i;
		i++;
	}
	if (j == -1)
		return (NULL);
	return (args[j + 1]);
}

/// @brief Get outin redirection args ("< {file_name}")
/// @param *input Prompt input,
/// @param *garbage Pointer to garbage collector.
/// @return Return a string in the format "< {file_name}"
char	*get_input(char *input_prompt, t_garbage *garbage)
{
	char	*input;
	int		i;
	int		j;

	i = get_char_pos(input_prompt, '<');
	j = 0;
	while (input_prompt[i + j] && \
	(input_prompt[i + j] == '<' || ft_isspace(input_prompt[i + j])))
		j++;
	while (input_prompt[i + j] && !ft_isspace(input_prompt[i + j]))
		j++;
	input = malloc((j + 1) * sizeof(char));
	ft_add_garbage(0, &garbage, input);
	ft_strlcpy(input, input_prompt + i, j + 1);
	return (input);
}
