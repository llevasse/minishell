/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/27 18:07:30 by mwubneh          ###   ########.fr       */
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
		printf("declare -x %s\n", print[j]);
	else if (print[j + 1] && !ft_strcmp(print[j + 1], "\"\""))
	{
		printf("declare -x %s=\"\"\n", print[j]);
		print[j + 1] = "";
	}
	else
	{
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
	while (p->export_args && p->export_args->key && !p->export_args->content)
	{
		if (!ft_strncmp(exp->key, "_=", 2))
			return ;
		exports = ft_joinf("%s", exp->key);
		if (!exports)
			return ;
		ft_add_garbage(1, &p->shell->at_exit_garbage, exports, p->shell);
		delete_duplicate_export(exp->key, p->shell);
		p->shell->env = insert_at_end(exports,
				p->shell->env, p->shell);
		p->export_args = p->export_args->next;
	}
}

/// @brief Reproduce export builtin behavior.
/// @param *prompt Pointer to prompt struct.
void	ft_export(t_prompt *p)
{
	char		*exports;
	char		**temp;
	t_export	*exp;

	temp = duplicate_env(p->shell);
	sort_tab_alpha(temp);
	if (!p->export_args)
		return (print_export(temp, p->shell));
	while (p->export_args && p->export_args->key)
	{
		exp = p->export_args;
		if (!ft_strncmp(exp->key, "_=", 2))
			return ;
		if (!p->export_args->content)
			export_empty(p, exports, exp);
		else
		{
			exports = ft_joinf("%s=%s", exp->key, exp->content);
			printf("%s\n", exports);
			if (!exports)
				return ;
			ft_add_garbage(1, &p->shell->at_exit_garbage, exports, p->shell);
			delete_duplicate_export(exp->key, p->shell);
			p->shell->env = insert_at_end(exports,
					p->shell->env, p->shell);
			p->export_args = p->export_args->next;
		}
	}
}
