/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:38:55 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/22 15:12:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	heredoc(char *input, t_prompt *prompt, t_garbage *garbage)
{
	char	*eof_str;
	int		i;
	
	i = get_char_pos(input, '<') + 2;
	eof_str = ft_strdup(input + i);
	i = 0;
	while (ft_isspace(*eof_str))
		eof_str++;
	ft_add_garbage(&garbage, eof_str);
	eof_str = ft_strsep(&eof_str, " ");
	ft_add_garbage(&garbage, eof_str);
	printf("Got EOF : %s|\n", eof_str);
	(void)prompt;
}
