/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:35:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/06 18:28:41 by llevasse         ###   ########.fr       */
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
	parse_args(prompt, prompt->args, garbage);
	input += i;
}

void	delete_redirection(char **args)
{
	int	i;

	i = 0;
//	printf("Delete\n");
	while (args[i])
	{
		if ((!ft_strcmp(args[i], ">") && ft_strlen(args[i]) == 1) || \
		(!ft_strcmp(args[i], "<") && ft_strlen(args[i]) == 1) || \
		(!ft_strcmp(args[i], ">>") && ft_strlen(args[i]) == 2) || \
		(!ft_strcmp(args[i], "<<") && ft_strlen(args[i]) == 2))
		{
			if (args[i + 1])
			{
//				printf("Delete |%s|%s|\n", args[i], args[i + 1]);
				delete_element_at_index(args, i);
				delete_element_at_index(args, i);
			}
			else
				delete_element_at_index(args, i);
		}
		else if (!ft_strncmp(args[i], "<<", 2) || !ft_strncmp(args[i], "<", 1) || \
		!ft_strncmp(args[i], ">>", 2) || !ft_strncmp(args[i], ">", 1))
			delete_element_at_index(args, i);
		else
			i++;
	}
}

void	printf_args(char **tab, char *prompt)
{
	int	i;

	i = 0;
	printf("%s", prompt);
	while (tab && tab[i])
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
	if (prompt && garbage)
		check_for_wildcard(prompt, args, 0, garbage);
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
		}
		i++;
	}
}
