/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:35:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/26 17:07:16 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get, and assign to t_prompt, args from inputed string.
/// @param *cmd Pointer to t_prompt,
/// @param *input Inputed string to get args from.
void	get_args(t_prompt *prompt, char *input, t_minishell *shell)
{
	int		i;

	i = 0;
	prompt->args = NULL;
	separate_cmd(prompt, input, shell);
	prompt->full_args = ft_split_args(prompt, input, ' ', shell);
	parse_args(prompt, prompt->full_args, shell);
	prompt->cmd = prompt->full_args[0]->s;
	if (!is_builtin(prompt->cmd))
		prompt->cmd = get_cmd_w_path(prompt, shell);
	if (!ft_strcmp(prompt->cmd, "export"))
		return (get_export_args(prompt, input));
	prompt->args = &prompt->full_args[1];
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

/// @brief Parse each quoted args and env variable,
/// and delete from tab each redirection and redirection file.
/// @param *prompt Pointer to prompt struct,
/// @param **args Pointer to args,
/// @param *garbage Pointer to garbage collector.
void	parse_args(t_prompt *prompt, t_arg **args, t_minishell *shell)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	check_for_wildcard(prompt, args, i, shell);
	while (args[i])
	{
		if (args[i] && args[i]->s[0] != 0 && \
			args[i]->s[ft_strlen(args[i]->s) - 1] == '\\' && args[i + 1])
		{
			args[i]->s[ft_strlen(args[i]->s) - 1] = 0;
			args[i]->s = ft_joinf("%s %s", args[i]->s, args[i + 1]->s);
			ft_add_garbage(0, &prompt->garbage, args[i]->s, prompt->shell);
			delete_arg_at_index(args, i + 1);
		}
		i++;
	}
}
