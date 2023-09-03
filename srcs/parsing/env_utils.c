/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:34:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/03 17:58:59 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_quote(char *str, t_minishell *shell)
{
	if (str[0] != '<' && str[0] != '>')
		return (str);
	str = ft_joinf("\"%s\"", str);
	ft_add_garbage(0, &shell->garbage, str, shell);
	return (str);
}

static void	error_code(char **str, t_minishell *shell)
{
	t_var	var;

	var.var = ft_itoa(shell->error_value);
	ft_add_garbage(0, &shell->garbage, var.var, shell);
	replace_str(str, "$?", var.var, shell);
}

/// @brief Check if a string contain a env variable.
/// @param **str Pointer to string to check.
/// @return Return 0 if no env variable and otherwise return 1
/// and replace env variable in *str with his content.
int	check_is_env_var(char **str, t_minishell *shell)
{
	t_var	var;

	var.i = 0;
	if (get_char_pos(*str, '$') == -1)
		return (0);
	while (var.i >= 0 && var.i < (int)ft_strlen(*str) && \
		get_char_pos((*str) + var.i, '$') >= 0)
	{
		var.var = get_env_var_name((*str) + var.i, shell);
		if (var.var[0] == '$' && var.var[1] == 0)
			var.i++;
		else if (!ft_strncmp("$?", var.var, 2))
			error_code(str, shell);
		else
		{
			var.env_var = ft_getenv(shell->env, var.var + 1, shell);
			if (!var.env_var)
				return (-1);
			var.env_var = add_quote(var.env_var, shell);
			replace_str(str, var.var, var.env_var, shell);
			var.i = get_char_pos(*str, '$');
		}
	}
	return (1);
}
