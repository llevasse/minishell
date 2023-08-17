/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/17 15:54:48 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_minishell	g_minishell;

char	**merge_tabs(char **tab1, char **tab2)
{
	int			nb;
	int			i;
	char		**new;

	nb = get_tab_size(tab1) + get_tab_size(tab2) + 1;
	new = malloc(nb * sizeof(char *));
	ft_add_garbage(0, &g_minishell.at_exit_garbage, new);
	i = 0;
	nb = 0;
	while (tab1[i])
		new[nb++] = tab1[i++];
	i = 0;
	while (tab2[i])
		new[nb++] = tab2[i++];
	return (new[nb] = NULL, new);
}
void	ft_export(t_prompt *prompt)
{
	char	**exports;

	if (prompt->export_args)
	{
		exports = convert_to_tab(prompt->export_args);
		g_minishell.env = merge_tabs(g_minishell.env, exports);
	}
	else
		printf_args(prompt->environ,"");
}
