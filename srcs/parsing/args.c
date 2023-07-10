/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:35:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/10 15:00:01 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get, and assign to t_prompt, args from inputed string.
/// @param *cmd Pointer to t_prompt,
/// @param *input Inputed string to get args from.
void	get_args(t_prompt *prompt, char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '|')
		i++;
	if (input[i] == '|')
		input[i - 1] = '\0';
	prompt->args = ft_split(input, ' ');
	if (!prompt->args)
		return (free(prompt));
	parse_args(prompt, prompt->args);
	input += i;
}

void	parse_args(t_prompt *prompt, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		check_is_env_var(&args[i]);
		if (!prompt->d_quotes && !prompt->quotes)
			check_quotes(prompt, &args[i]);
		i++;
	}
}
