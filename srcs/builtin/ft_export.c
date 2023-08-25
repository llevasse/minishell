/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 01:10:01 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_listing(char **env, int i, t_minishell *shell);

/// @brief print content of env.
/// @param **env array of chars *.
void	print_export(char **env, t_minishell *shell)
{
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		if (ft_strncmp("_=", env[i], 2))
			export_listing(env, i, shell);
		i++;
	}
}

/// @brief print content of env[i].
/// @param **env array of chars *,
/// @param i index of which **env element to print
void	export_listing(char **env, int i, t_minishell *shell)
{
	int		j;
	char	**print;

	j = 0;
	print = ft_split(env[i++], '=');
	ft_add_garbage(0, &shell->garbage, print, shell);
	if (!print[j + 1])
		printf("declare -x %s", print[j]);
	else
		printf("declare -x %s=\"", print[j]);
	ft_add_garbage(0, &shell->garbage, print[j++], shell);
	while (print[j])
	{
		printf("%s", print[j]);
		ft_add_garbage(0, &shell->garbage, print[j++], shell);
		if (print[j])
			printf("=");
	}
	if (j > 1)
		printf("\"");
	printf("\n");
}

/// @brief Delete first instance found of *key in shell->env.
/// @param *key Variable name to delete.
void	delete_duplicate_export(char *key, t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i] && \
	ft_strncmp(key, shell->env[i], ft_strlen(key)))
		i++;
	if (shell->env[i])
		delete_element_at_index(shell->env, i);
}

/// @brief Reproduce export builtin behavior.
/// @param *prompt Pointer to prompt struct.
void	ft_export(t_prompt *prompt)
{
	char		*exports;
	char		**temp;
	t_export	*exp;

	temp = duplicate_env(prompt->shell);
	sort_tab_alpha(temp);
	if (prompt->export_args)
	{
		exp = prompt->export_args;
		if (!ft_strncmp(exp->key, "_=", 2))
			return ;
		exports = ft_joinf("%s=%s", exp->key, exp->content);
		if (!exports)
			return ;
		ft_add_garbage(1, &prompt->shell->at_exit_garbage, exports, prompt->shell);
		delete_duplicate_export(exp->key, prompt->shell);
		prompt->shell->env = insert_alpha(exports,
				prompt->shell->env, prompt->shell);
	}
	else
		print_export(temp, prompt->shell);
}
