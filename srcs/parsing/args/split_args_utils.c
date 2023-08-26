/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:34:09 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/26 23:23:44 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	we_go_forward(t_arg **res, int *word, t_prompt *prompt)
{
	(*word)++;
	res[*word] = NULL;
	prompt->args = res;
}

int	is_redir_symbol(t_arg *arg, int is_alone)
{
	if (arg->quote)
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
	int	word;

	word = v->word;
	v->res[word]->quote = v->str[v->i];
	v->res[word]->s = get_split_quote(prompt,
			&v->str, &v->i, word - 1);
	if (word > 0 && (v->str[v->i - \
			(ft_strlen(v->res[word]->s) + 3)] != v->p || \
			 is_redir_symbol(v->res[word - 1], 1)))
	{
		v->res[v->word - 1]->s = ft_strjoin(v->res[v->word - 1]->s,
				v->res[v->word]->s);
		ft_add_garbage(0, &shell->garbage, v->res[v->word - 1]->s, shell);
		v->res[v->word--] = NULL;
	}
	return (1);
}

void	get_arg_not_quoted(t_prompt *prompt, t_var_2 *var, t_minishell *shell)
{
	var->res[var->word]->s = get_word_arg(var->str, var->p, var->i, shell);
	var->i += ft_strlen(var->res[var->word]->s);
	if (var->word > 0 && (var->str[var->i - \
		(ft_strlen(var->res[var->word]->s) + 1)] != var->p || \
		is_redir_symbol(var->res[var->word - 1], 1)))
	{
		var->res[var->word - 1]->s = ft_strjoin(var->res[var->word - 1]->s, \
			var->res[var->word]->s);
		ft_add_garbage(0, &shell->garbage, var->res[var->word - 1]->s, shell);
		var->res[var->word--] = NULL;
	}
	check_is_env_var(prompt, &var->res[var->word]->s, shell);
}
