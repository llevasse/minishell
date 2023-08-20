/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:35:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/20 17:50:19 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get, and assign to t_prompt, args from inputed string.
/// @param *cmd Pointer to t_prompt,
/// @param *input Inputed string to get args from.
void	get_args(t_prompt *prompt, char *input, t_garbage *garbage)
{
	int		i;

	i = 0;
	prompt->args = NULL;
	if (!ft_strcmp(prompt->cmd, "export"))
		return (get_export_args(prompt, input, garbage));
	separate_cmd(prompt, input, garbage);
	prompt->args = ft_split_args(prompt, input, ' ', garbage);
	parse_args(prompt, prompt->args, garbage);
	input += i;
}

/// @brief Get number of element in **tab.
/// @param **tab Pointer to pointers of char.
/// @return Return number of element in tab.
int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void	printf_args(t_arg **tab, char *prompt)
{
	int	i;

	i = 0;
	printf("%s\n", prompt);
	while (tab && tab[i] && tab[i]->s)
		printf("%s\n", tab[i++]->s);
	printf("%s\n", tab[i]->s);
}

/// @brief Parse each quoted args and env variable,
/// and delete from tab each redirection and redirection file.
/// @param *prompt Pointer to prompt struct,
/// @param **args Pointer to args,
/// @param *garbage Pointer to garbage collector.
void	parse_args(t_prompt *prompt, t_arg **args, t_garbage *garbage)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	check_for_wildcard(prompt, args, i, garbage);
	while (args[i])
	{
		if (args[i] && args[i]->s[0] != 0 &&
			args[i]->s[ft_strlen(args[i]->s) - 1] == '\\' && args[i + 1])
		{
			args[i]->s[ft_strlen(args[i]->s) - 1] = 0;
			args[i]->s = ft_joinf("%s %s", args[i]->s, args[i + 1]->s);
			ft_add_garbage(0, &garbage, args[i]->s);
			delete_arg_at_index(args, i + 1);
		}
		i++;
	}
}
