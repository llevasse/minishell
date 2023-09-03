/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:35:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/03 17:24:46 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// cases like prompt is "< text" or whatever 
int	i_dont_like_people_doing_this(t_prompt *p)
{
	int	i;

	i = 0;
	if (is_redir_symbol(p->full_args[i], 0))
	{
		while (p->full_args[i] && is_redir_symbol(p->full_args[i], 0))
			i++;
	}
	if (i == 0)
		return (1);
	p->cmd = NULL;
	if (!p->full_args[i])
		return ((void)(p->args = &p->full_args[0]), 0);
	p->cmd = p->full_args[i]->s;
	if (!is_builtin(p->cmd) && p->cmd[0] != '/')
		p->cmd = get_cmd_w_path(p, p->shell);
	delete_arg_at_index(p->full_args, i);
	p->args = &p->full_args[0];
	return (0);
}

/// @brief Get, and assign to t_prompt, args from inputed string.
/// @param *cmd Pointer to t_prompt,
/// @param *input Inputed string to get args from.
void	get_args(t_prompt *prompt, char *input, t_minishell *shell)
{
	int	i = -1;
	prompt->args = NULL;
	separate_cmd(prompt, input, shell);
	if (!input || !input[0])
		return ;
	prompt->full_args = ft_split_args(prompt, input, ' ', shell);
	while (prompt->full_args[++i])
		printf("arg : |%s| with quote : %c\n", prompt->full_args[i]->s, prompt->full_args[i]->quote);
	if (i_dont_like_people_doing_this(prompt))
	{
		if (!prompt->full_args[0])
			return ;
		prompt->cmd = prompt->full_args[0]->s;
		if (!is_builtin(prompt->cmd) && prompt->cmd[0] != '/')
			prompt->cmd = get_cmd_w_path(prompt, shell);
		prompt->args = NULL;
		if (prompt->full_args[1])
			prompt->args = &prompt->full_args[1];
	}
	if (prompt->cmd && prompt->args && !ft_strcmp(prompt->cmd, "export"))
		return (get_export_args(prompt));
	parse_args(prompt, prompt->args, shell);
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
		if (args[i] && args[i]->s[0] == 0 && !args[i]->quote)
			delete_arg_at_index(args, i);
		i++;
	}
}
