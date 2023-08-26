/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:52:58 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 20:23:54 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prompt_null(t_prompt *prompt)
{
	prompt->old_stdout = -1;
	prompt->old_stdin = -1;
	prompt->has_redir = 0;
	prompt->has_output = 0;
	prompt->has_exec = 0;
	prompt->args = NULL;
	prompt->full_args = NULL;
	prompt->export_args = NULL;
	prompt->next_cmd = NULL;
	prompt->prev_cmd = NULL;
	prompt->exec_fd[0] = -1;
	prompt->exec_fd[1] = -1;
	prompt->exec_pid = -1;
}

/// @brief Allocate memory and assign values to t_prompt.
/// @param *input Inputed string to get command from.
/// @return Return pointer to t_prompt or NULL if something failed.
t_prompt	*init_prompt(char *input, t_garbage *garbage, t_minishell *shell)
{
	t_prompt	*prompt;

	if (get_char_occurance(input, '"') % 2 != 0 || \
		get_char_occurance(input, 39) % 2 != 0)
		return (NULL);
	prompt = malloc(sizeof(struct s_prompt));
	ft_add_garbage(0, &garbage, prompt, shell);
	set_prompt_null(prompt);
	prompt->environ = shell->env;
	prompt->shell = shell;
	prompt->garbage = garbage;
//	get_cmd(&input, prompt, shell);
//	if (!prompt->cmd && errno != 12)
//		return ((void)(errno = 127), prompt);
	get_args(prompt, input, shell);
	prompt->full_args = get_full_args(prompt, shell);
	return (prompt);
}

void	ft_add_prompt(t_prompt **lst, t_prompt *new)
{
	t_prompt	*temp;

	if (!new)
		return (ft_exit(new->shell, NULL));
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
