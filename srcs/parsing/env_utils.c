/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 12:34:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/27 19:41:39 by llevasse         ###   ########.fr       */
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

static void	error_code(t_prompt *p, char **str, t_minishell *shell)
{
	t_var	var;

	var.var = ft_itoa(p->shell->error_value);
	ft_add_garbage(0, &shell->garbage, var.var, shell);
	replace_str(str, "$?", var.var, p->shell);
}

/// @brief Check if a string contain a env variable.
/// @param **str Pointer to string to check.
/// @return Return 0 if no env variable and otherwise return 1
/// and replace env variable in *str with his content.
int	check_is_env_var(t_prompt *p, char **str, t_minishell *shell)
{
	t_var	var;

	var.i = 0;
	if (get_char_pos(*str, '$') == -1)
		return (0);
	while (var.i >= 0 && var.i < (int)ft_strlen(*str) && \
		get_char_pos((*str) + var.i, '$') >= 0)
	{
		var.var = get_env_var_name((*str) + var.i, p->shell);
		if (var.var[0] == '$' && var.var[1] == 0)
			var.i++;
		else if (!ft_strncmp("$?", var.var, 2))
			error_code(p, str, shell);
		else
		{
			var.env_var = ft_getenv(p->environ, var.var + 1, p->shell);
			if (!var.env_var)
				return (-1);
			var.env_var = add_quote(var.env_var, p->shell);
			replace_str(str, var.var, var.env_var, p->shell);
			var.i = get_char_pos(*str, '$');
		}
	}
	return (1);
}
