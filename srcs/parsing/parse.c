/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:51:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/06 23:00:22 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *input)
{
	t_cmd	*cmd;

	cmd = init_cmd(input);
	check_cmd(cmd);
	printf("\n");
}

void	check_cmd(t_cmd *cmd)
{
	int	i;
	
	if (!cmd)
		return ;
	if (!ft_strncmp(cmd->cmd, "cd", 2))
		return (ft_cd());	
	printf("%s unknown command with argument(s) ", cmd->cmd);
	i = 0;
	while (cmd->args && cmd->args[i])
		printf("%s ", cmd->args[i++]);
}

t_cmd *init_cmd(char *input)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(struct s_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_strsep(&input, " ");
	if (!*input)
		return (cmd);
	cmd->args = NULL;
	get_args(cmd, input);
	return (cmd);
}

void get_args(t_cmd *cmd, char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '|')
		i++;
	if (input[i] == '|')
		input[i - 1] = '\0';
	cmd->args = ft_split(input, ' ');
	if (!cmd->args)
		return (free(cmd));
	input += i;
}

