/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:35:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/01 22:30:40 by llevasse         ###   ########.fr       */
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
	if (!ft_strcmp(prompt->cmd, "export"))
		return (get_export_args(prompt, input, garbage));
	separate_cmd(prompt, input, garbage);
	prompt->args = ft_split_args(prompt, input, ' ', garbage);
	if (!prompt->args)
		return (ft_exit(garbage));
	parse_args(prompt, prompt->args, garbage);
	input += i;
}

void	delete_redirection(int i, char **args)
{
	if ((!ft_strcmp(args[i], ">") && ft_strlen(args[i]) == 1) || \
	(!ft_strcmp(args[i], "<") && ft_strlen(args[i]) == 1) || \
	(!ft_strcmp(args[i], ">>") && ft_strlen(args[i]) == 2) || \
	(!ft_strcmp(args[i], "<<") && ft_strlen(args[i]) == 2))
	{
		delete_element_at_index(args, i);
		delete_element_at_index(args, i);
	}
	else if (!ft_strncmp(args[i], "<<", 2) || !ft_strncmp(args[i], "<", 1) || \
	!ft_strncmp(args[i], ">>", 2) || !ft_strncmp(args[i], ">", 1))
		delete_element_at_index(args, i);
}

void	printf_args(char **tab)
{
	int	i;

	i = 0;
	printf("ARGS:");
	while (tab[i])
		printf(" %s", tab[i++]);
	printf("\n");
}

/// @brief Parse each quoted args and env variable,
/// and delete from tab each redirection and redirection file.
/// @param *prompt Pointer to prompt struct,
/// @param **args Pointer to args,
/// @param *garbage Pointer to garbage collector.
void	parse_args(t_prompt *prompt, char **args, t_garbage *garbage)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] && args[i][ft_strlen(args[i]) - 1] == '\\' && args[i + 1])
		{
			args[i] = ft_joinf("%s %s", args[i], args[i + 1]);
			ft_add_garbage(0, &garbage, args[i]);
			delete_element_at_index(args, i + 1);
		}
		if (prompt && garbage)
		{
			if (!prompt->d_quotes && !prompt->quotes)
				check_quotes(prompt, &args[i], garbage);
			if (!prompt->quotes)
				check_is_env_var(&args[i], garbage);
			check_for_wildcard(prompt, args, i, garbage);
		}
		delete_redirection(i, args);
		i++;
	}
}

///	@brief Delete element in tab at index.
/// @param **tab Pointer to tab,
/// @param index Index of element to delete
void	delete_element_at_index(char **tab, int index)
{
	while (tab[index])
	{
		tab[index] = tab[index + 1];
		index++;
	}
}
