/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:27:41 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/17 15:23:04 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**merge_tabs(char **tab1, char **tab2, t_garbage *garbage)
{
	int			nb;
	int			i;
	char		**new;

	nb = get_tab_size(tab1) + get_tab_size(tab2) + 1;
	new = malloc(nb * sizeof(char *));
	ft_add_garbage(0, &garbage, new);
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
		exports = convert_to_tab(prompt->export_args, prompt->garbage);
		printf_args(exports, "Assign :");
		prompt->environ = merge_tabs(prompt->environ, exports, prompt->garbage);
	}
	else
		printf_args(prompt->environ,"");
}
