/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:34:09 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/26 17:17:41 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	we_go_forward(t_arg **res, int *word, t_prompt *prompt)
{
	(*word)++;
	res[*word] = NULL;
	prompt->args = res;
}

int	go_get_that_quote(t_prompt *prompt, t_var_2 *var, t_minishell *shell)
{
	var->res[var->word]->quote = var->str[var->i];
	var->res[var->word]->s = get_split_quote(prompt,
			&var->str, &var->i, var->word - 1);
	if (var->word > 0 && var->str[var->i - \
			(ft_strlen(var->res[var->word]->s) + 3)] != var->p)
	{
		var->res[var->word - 1]->s = ft_strjoin(var->res[var->word - 1]->s,
				var->res[var->word]->s);
		ft_add_garbage(0, &shell->garbage, var->res[var->word - 1]->s, shell);
		var->res[var->word--] = NULL;
	}
	return (1);
}

void	get_arg_not_quoted(t_prompt *prompt, t_var_2 *var, t_minishell *shell)
{
	var->res[var->word]->s = get_word_arg(var->str, var->p, var->i, shell);
	var->i += ft_strlen(var->res[var->word]->s);
	check_is_env_var(prompt, &var->res[var->word]->s, shell);
	if (var->word > 0 && var->str[var->i - \
		(ft_strlen(var->res[var->word]->s) + 1)] != var->p)
	{
		var->res[var->word - 1]->s = ft_strjoin(var->res[var->word - 1]->s, \
			var->res[var->word]->s);
		ft_add_garbage(0, &shell->garbage, var->res[var->word - 1]->s, shell);
		var->res[var->word--] = NULL;
	}
}
