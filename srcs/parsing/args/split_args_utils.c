/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:34:09 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/29 14:00:50 by llevasse         ###   ########.fr       */
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

int	go_get_that_quote(t_prompt *prompt, t_var_2 *v, t_minishell *shell)
{
	int	quote;

	v->res[v->word]->quote = v->str[v->i];
	quote = v->res[v->word]->quote;
	v->res[v->word]->s = get_split_quote(prompt, &v->str, &v->i);
	if (v->word > 0 && (v->str[v->i - \
			(ft_strlen(v->res[v->word]->s) + 3)] != v->p || \
			is_redir_symbol(v->res[v->word - 1], 1)))
	{
		v->res[v->word - 1]->s = ft_strjoin(v->res[v->word - 1]->s,
				v->res[v->word]->s);
		ft_add_garbage(0, &shell->garbage, v->res[v->word - 1]->s, shell);
		v->res[v->word--] = NULL;
	}
	if (quote == '"')
	{
		if (v->word >= 0 && !ft_strncmp(v->res[v->word]->s, "<<", 2))
			return (1);
		check_is_env_var(prompt, &v->res[v->word]->s, shell);
	}
	return (1);
}

void	get_arg_not_quoted(t_prompt *prompt, t_var_2 *var, t_minishell *shell)
{
	var->res[var->word]->s = get_word_arg(var->str, var->p, var->i, shell);
	var->i += ft_strlen(var->res[var->word]->s);
	if (var->word > 0 && (var->str[var->i - \
		(ft_strlen(var->res[var->word]->s) + 1)] != var->p || \
		is_redir_symbol(var->res[var->word - 1], 1)) && \
		!is_redir_symbol(var->res[var->word], 0))
	{
		var->res[var->word - 1]->s = ft_strjoin(var->res[var->word - 1]->s, \
			var->res[var->word]->s);
		ft_add_garbage(0, &shell->garbage, var->res[var->word - 1]->s, shell);
		var->res[var->word--] = NULL;
	}
	if (!ft_strncmp(var->res[var->word]->s, "<<", 2))
		return ;
	if (check_is_env_var(prompt, &var->res[var->word]->s, shell) == -1)
	{
		if (prompt->cmd && !ft_strcmp(prompt->cmd, "export"))
		{
			var->res[var->word]->s += get_char_pos(var->res[var->word]->s, '$');
			return ;
		}
		var->res[var->word] = NULL;
	}
}
