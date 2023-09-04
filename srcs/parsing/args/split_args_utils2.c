/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:14:23 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/04 11:24:53 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(char **str, t_minishell *shell)
{
	t_var	var;

	var.i = get_char_pos(*str, '$');
	while (var.i >= 0 && var.i < (int)ft_strlen(*str) && \
		get_char_pos((*str) + var.i, '$') >= 0)
	{
		var.var = get_env_var_name((*str) + var.i, shell);
		replace_str(str, var.var, var.env_var, shell);
		var.i = get_char_pos(*str, '$');
	}
}

int	go_get_that_quote(t_prompt *prompt, t_var_2 *v, t_minishell *shell)
{
	v->res[v->word]->quote = v->str[v->i];
	v->res[v->word]->s = get_split_quote(prompt, &v->str, &v->i);
	if (v->word > 0 && (v->str[v->i - \
			(ft_strlen(v->res[v->word]->s) + 3)] != v->p || \
			is_redir_symbol(v->res[v->word - 1], 1)))
	{
		v->res[v->word - 1]->s = ft_strjoin(v->res[v->word - 1]->s,
				v->res[v->word]->s);
		v->res[v->word - 1]->joined_quote += v->res[v->word]->quote;
		ft_add_garbage(0, &shell->garbage, v->res[v->word - 1]->s, shell);
		v->res[v->word--] = NULL;
	}
	if (ft_strncmp(v->res[v->word]->s, "<<", 2))
	{
		if (check_is_env_var(&v->res[v->word]->s, shell) == -1)
			remove_env_var(&v->res[v->word]->s, shell);
	}
	return (1);
}

void	get_arg_not_quoted(t_var_2 *var, t_minishell *shell)
{
	if (var->str[var->i] == '$')
		return (get_env_var_as_arg(var, shell));
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
	var->res[var->word + 1] = NULL;
}
