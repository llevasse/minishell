/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:22:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/16 15:07:01 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirection(char *input, t_prompt *first_prompt, t_garbage *garbage)
{
	if (get_char_pos(input, '>') != -1)
		set_output(input, first_prompt, garbage);
//	if (get_char_pos(input, '<') != -1)
//	
//	if (get_char_pos(input, '|') != -1)
}

void	set_output(char *input, t_prompt *input_prompt, t_garbage *garbage)
{
	t_prompt	*prompt;
	int			i;

	i = get_char_pos(input, '>');
	if (input[i + 1] == '>')
		return (set_output_append(input, input_prompt, garbage));
	while (input[i] && input[i] == '>' && isspace(input[i]))
		i++;
	if (!input[i])
		return ((void)printf("File does not exist\n"));
	prompt = init_prompt(input + i, garbage);
	prompt->input_prompt = input_prompt;
	input_prompt->output_prompt = prompt;
}

void	set_output_append(char *input, t_prompt *input_prompt, t_garbage *garbage)
{
	printf("Cc je append a l'output\n");
	(void)input;
	(void)input_prompt;
	(void)garbage;
}
