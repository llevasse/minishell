/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:52:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/21 21:30:20 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

void	print_prompt(t_prompt p)
{
	printf("prompt.cmd = %s\n", p.cmd);
	printf_args(p.args, "prompt.args :");
	printf_args(p.full_args, "prompt.full_args :");
	printf("prompt.old_stdout = %d\n", p.old_stdout);
	printf("prompt.old_stdint = %d\n", p.old_stdin);
	printf("prompt.has_redir = %d\n", p.has_redir);
	printf("prompt.tmp_fd = %d\n", p.tmp_fd);
	printf("prompt.exec_fd[0] = %d\n", p.exec_fd[0]);
	printf("prompt.exec_fd[1] = %d\n\n\n\n\n", p.exec_fd[1]);
}

void	set_prompt_null(t_prompt *prompt)
{
	prompt->write_fd = -1;
	prompt->old_stdout = -1;
	prompt->old_stdin = -1;
	prompt->has_redir = 0;
	prompt->args = NULL;
	prompt->full_args = NULL;
	prompt->export_args = NULL;
	prompt->next_cmd = NULL;
	prompt->prev_cmd = NULL;
	prompt->exec_fd[0] = -1;
	prompt->exec_fd[1] = -1;
}

/// @brief Allocate memory and assign values to t_prompt.
/// @param *input Inputed string to get command from.
/// @return Return pointer to t_prompt or NULL if something failed.
t_prompt	*init_prompt(char *input, t_garbage *garbage, char **env)
{
	t_prompt	*prompt;

	prompt = malloc(sizeof(struct s_prompt));
	ft_add_garbage(0, &garbage, prompt);
	set_prompt_null(prompt);
	prompt->environ = env;
	prompt->garbage = garbage;
	get_cmd(&input, prompt, garbage);
	if (!prompt->cmd && errno != 12)
		return ((void)(errno = 127), prompt);
	get_args(prompt, input, garbage);
	prompt->full_args = get_full_args(prompt, garbage);
	return (prompt);
}

void	ft_add_prompt(t_prompt **lst, t_prompt *new)
{
	t_prompt	*temp;

	if (!new)
		return (ft_exit(g_minishell.garbage, NULL));
	if (*lst)
	{
		temp = *lst;
		while (temp->next_cmd != NULL)
			temp = temp->next_cmd;
		temp->next_cmd = new;
		new->prev_cmd = temp;
		return ;
	}
	*lst = new;
}
