/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:34:09 by mwubneh           #+#    #+#             */
/*   Updated: 2023/09/03 18:30:19 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_set(t_var_2 *var, char *s, char c, t_minishell *shell)
{
	var->str = s;
	var->p = c;
	var->word = 0;
	var->res = alloc_tab_args(s, c, shell);
	var->i = skip_char(s, c, 0);
}

void	we_go_forward(t_arg **res, int *word, t_prompt *prompt)
{
	(*word)++;
	res[*word] = NULL;
	prompt->args = res;
}

int	is_redir_symbol(t_arg *arg, int is_alone)
{
	if (!arg || arg->quote)
		return (0);
	if (is_alone && !ft_strcmp(arg->s, "<"))
		return (1);
	if (is_alone && !ft_strcmp(arg->s, "<<"))
		return (1);
	if (is_alone && !ft_strcmp(arg->s, ">"))
		return (1);
	if (is_alone && !ft_strcmp(arg->s, ">>"))
		return (1);
	if (!is_alone && !ft_strncmp(arg->s, "<", 1))
		return (1);
	if (!is_alone && !ft_strncmp(arg->s, "<<", 2))
		return (1);
	if (!is_alone && !ft_strncmp(arg->s, ">", 1))
		return (1);
	if (!is_alone && !ft_strncmp(arg->s, ">>", 2))
		return (1);
	return (0);
}
