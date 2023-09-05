/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/05 23:00:15 by llevasse         ###   ########.fr       */
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
	sort_tab_alpha(env);
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
	int		empty;

	j = 0;
	empty = get_char_pos(env[i], '=') + 1;
	print = ft_split(env[i++], '=');
	ft_add_garbage(0, &shell->garbage, print, shell);
	if (!empty)
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
	if (empty)
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

void	export_empty(t_prompt *p, char *exports, t_export *exp)
{
	if (!ft_strncmp(exp->key, "_=", 2) || \
		!!ft_getenv(p->shell->env, exp->key, p->shell))
		return ;
	exports = ft_strdup(exp->key);
	ft_add_garbage(1, &p->shell->at_exit_garbage, exports, p->shell);
	delete_duplicate_export(exports, p->shell);
	p->shell->env = insert_at_end(exports,
			p->shell->env, p->shell);
	exp = exp->next;
}

/// @brief Reproduce export builtin behavior.
/// @param *prompt Pointer to prompt struct.
void	ft_export(t_prompt *p)
{
	char		*exports;
	t_export	*exp;

	exp = p->export_args;
	while (exp)
	{
		if (!exp->key || !ft_strncmp(exp->key, "_=", 2))
			return ;
		if (!p->export_args->content)
			export_empty(p, exports, exp);
		else
		{
			exports = ft_joinf("%s=%s", exp->key, exp->content);
			if (!exports)
				return ;
			ft_add_garbage(1, &p->shell->at_exit_garbage, exports, p->shell);
			delete_duplicate_export(exp->key, p->shell);
			p->shell->env = insert_at_end(exports,
					p->shell->env, p->shell);
		}
		exp = exp->next;
	}
}
