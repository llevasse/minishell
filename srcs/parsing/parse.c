/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:51:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/06 18:43:02 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *input)
{
	t_cmd	*cmd;
	int	i;

	cmd = init_cmd(input);
	if (!cmd)
		return ;
	printf("%s unknown command with argument(s) ", cmd->cmd);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	printf("\n");
}

t_cmd *init_cmd(char *input)
{
	t_cmd	*cmd;
	int	i;

	cmd = malloc(sizeof(struct s_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_strsep(&input, " ");
	if (!*input)
		return (cmd);
	cmd->args = NULL;
	i = 0;
	while (input[i] && input[i] != '|')
		i++;
	if (input[i] == '|')
		input[i - 1] = '\0';
	cmd->args = ft_split(input, ' ');
	if (!cmd->args)
		return (free(cmd), NULL);
	input += i;
	return (cmd);
}
