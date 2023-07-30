/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:38:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/30 15:24:15 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separate_cmd(t_prompt *prompt, char *input, t_garbage *garbage)
{
	int	pos = get_nearer_separator_pos(input);
	if (pos == -1)
		return ;
	input[pos++] = 0;
	while (input[pos] && 
			(ft_is_in_str("|&;", input[pos]) || ft_isspace(input[pos])))
		pos++;
	if (!input[pos])
		return ;
	input += pos;
	ft_add_prompt(&prompt, init_prompt(input, garbage));
}

int	get_nearer_separator_pos(char *input)
{
	int	pos;

	pos = -1;
	if (get_separator_pos(input, "|") != -1 && pos <= get_separator_pos(input, "|"))
		pos = get_separator_pos(input, "|");
	if (get_separator_pos(input, "||") != -1 && pos <= get_separator_pos(input, "||"))
		pos = get_separator_pos(input, "||");
	if (get_separator_pos(input, "&&") != -1 && pos <= get_separator_pos(input, "&&"))
		pos = get_separator_pos(input, "&&");
	if (get_separator_pos(input, ";") != -1 && pos <= get_separator_pos(input, ";"))
		pos = get_separator_pos(input, ";");
	return (pos);
}

int	is_char_quoted(char *str, int pos)
{
	if (get_char_pos(str + pos, '"') != -1 && \
		get_char_occurance(str + pos, '"') % 2 != 0)
		return (1);
	if (get_char_pos(str + pos, 39) != -1 && \
		get_char_occurance(str + pos, 39) % 2 != 0)
		return (1);
	return (0);
}

int	get_separator_pos(char *input, char *separator)
{
	int	pos;

	pos = -1;
	if (get_substr_pos(input, separator) != -1)
	{
		pos = get_substr_pos(input, separator);
		while (is_char_quoted(input, pos + ft_strlen(separator)))
		{
			pos += get_substr_pos(input + pos + ft_strlen(separator), separator);
			if (pos == -1)
				break ;
		}
	}
	return (pos);
}
