/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_as_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:24:19 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/04 14:06:25 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_var(t_var_2 *var, t_minishell *shell)
{
	char	*var_name;

	var_name = get_env_var_name(var->str + var->i, shell);
	var->i += ft_strlen(var_name);
	if (check_is_env_var(&var_name, shell) == -1)
	{
		var->res[var->word] = NULL;
		if (var->word)
			return ((void)(var->res[var->word--]), NULL);
		return (NULL);
	}
	return (var_name);
}

static int join_condition(char *var_name, char **split, t_var_2 *var, t_minishell *shell)
{
	if (var->word > 0 && (var->str[var->i - \
		(ft_strlen(var_name) + 1)] != var->p || \
		is_redir_symbol(var->res[var->word - 1], 1)) && split[0])
	{
		var->res[var->word - 1]->s = ft_strjoin(var->res[var->word - 1]->s, \
			split[0]);
		ft_add_garbage(0, &shell->garbage, var->res[var->word - 1]->s, shell);
		var->res[var->word--] = NULL;
		return (1);
	}
	return (0);
}

void	get_env_var_as_arg(t_var_2 *var, t_minishell *shell)
{
	char	*var_name;
	char	*var_name_dup;
	char	**split;
	int		i;
	t_arg	**arg;

	var_name_dup = get_env_var_name(var->str + var->i, shell);
	var_name = get_var(var, shell);
	if (!var_name)
		return ;
	split = ft_split(var_name, ' ');
	add_split_to_garbage(split, shell);
	i = join_condition(var_name_dup, split, var, shell);
	if (!split[i])
		return ;
	arg = malloc((get_tab_size(split) + 1) * sizeof(t_arg));
	ft_add_garbage(0, &shell->garbage, arg, shell);
	while (split[i])
	{
		arg[i] = init_arg(shell);
		arg[i]->s = split[i];
		arg[i++]->quote = '"';
	}
	arg[i] = NULL;
	var->res = insert_tab_at_index(var->res, arg, var->word, shell);
	var->word += get_tab_size(split) - 1;
}
