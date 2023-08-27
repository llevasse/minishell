/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:02 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/27 22:29:44 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Replace content of env variable or add it.
/// @param *var_name New env variable name,
/// @param *new_value New value for env variable.
void	replace_env(char *var_name, char *new_value, t_minishell *shell)
{
	int	i;

	i = 0;
	var_name = ft_strjoin(var_name, "=");
	ft_add_garbage(0, &shell->garbage, var_name, shell);
	new_value = ft_strjoin(var_name, new_value);
	if (!new_value)
		return ;
	ft_add_garbage(1, &shell->at_exit_garbage, new_value, shell);
	delete_duplicate_export(var_name, shell);
	while (shell->env[i])
	{
		if (!ft_strncmp(var_name, shell->env[i], ft_strlen(var_name)))
		{
			shell->env[i] = new_value;
			return ;
		}
		i++;
	}
	shell->env = insert_at_end(new_value, shell->env, shell);
}

/// @brief duplicate shell->env.
char	**duplicate_env(t_minishell *shell)
{
	char	**new;
	int		i;

	new = malloc((get_tab_size(shell->env) + 1) * sizeof(char *));
	ft_add_garbage(0, &shell->garbage, new, shell);
	i = 0;
	while (shell->env[i])
	{
		new[i] = shell->env[i];
		new[i++ + 1] = NULL;
	}
	return (new);
}

/// @brief Print content of shell->env at i index.
static int	print_env(t_minishell *shell, int i)
{
	char	**print;
	int		j;

	j = 0;
	if (get_char_pos(shell->env[i], '=') == -1)
		return (1);
	print = ft_split(shell->env[i++], '=');
	ft_add_garbage(0, &shell->garbage, print, shell);
	printf("%s=", print[j]);
	ft_add_garbage(0, &shell->garbage, print[j++], shell);
	while (print[j])
	{
		printf("%s", print[j]);
		ft_add_garbage(0, &shell->garbage, print[j++], shell);
		if (print[j])
			printf("=");
	}
	printf("\n");
	return (i);
}

/// @brief reproduce env builtin behavior.
void	ft_env(t_minishell *shell)
{
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp("_=", shell->env[i], 2))
			print_env(shell, i);
		i++;
	}
	ft_printf("_=/usr/bin/env\n");
}
