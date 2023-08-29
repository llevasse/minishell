/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:38:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/29 23:45:35 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check for separation of cmd and add it to prompt->next_cmd.
/// @param *prompt Pointer to prompt struct,
/// @param *input String of the prompt input,
/// @param *garbage Pointer to garbage collector.
void	separate_cmd(t_prompt *prompt, char *input, t_minishell *shell)
{
	int	pos;

	pos = get_nearer_separator_pos(input);
	if (pos == -1)
		return ;
	input[pos++] = 0;
	while (input[pos] && \
		(ft_is_in_str("|&;", input[pos]) || ft_isspace(input[pos])))
		pos++;
	if (!input[pos])
		return ;
	input += pos;
	pos = prompt->lvl + 1;
	ft_add_prompt(&prompt, init_prompt(input, shell->garbage, prompt->shell, pos));
}

/// @brief Search for the closest cmd separator in *input.
/// @param *input Str to search in,
/// @return Return position of closest separator or -1 if there is none.
int	get_nearer_separator_pos(char *input)
{
	int	pos;

	pos = -1;
	if (get_separator_pos(input, "|") != -1 && \
		pos <= get_separator_pos(input, "|"))
		pos = get_separator_pos(input, "|");
	return (pos);
}

/// @brief Search if char at pos in *str is between quotes.
/// @param *str Str to check in,
///	@param pos Position of char to check.
/// @return 1 if there is an odd number of quotes after given pos if *str.
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

/// @brief get position of sep that is NOT quoted.
/// @param *input Str to search sep,
///	@param *sep Str to search.
/// @return return position of sep or -1 if none is found.
int	get_separator_pos(char *input, char *sep)
{
	int	pos;
	int	safe;

	pos = -1;
	if (get_substr_pos(input, sep) != -1)
	{
		pos = get_substr_pos(input, sep);
		while (is_char_quoted(input, pos))
		{
			safe = get_substr_pos(input + pos + ft_strlen(sep), sep);
			if (safe == -1)
				return (-1);
			pos += safe + 1;
		}
	}
	return (pos);
}
