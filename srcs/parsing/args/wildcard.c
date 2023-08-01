/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:41:19 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/01 09:45:40 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO store args in chain instead of array

void	check_for_wildcard(t_prompt *prompt, t_garbage *garbage)
{
	char	*pwd;

	if (get_char_pos(prompt->args->s, '*') == -1)
		return ;
	pwd = get_pwd(garbage);
	printf("Pwd : %s\n", pwd);
	(void)prompt;
}

char	*get_pwd(t_garbage *garbage)
{
	char	*pwd;
	size_t	size;

	size = 128;
	pwd = malloc(sizeof(char) * (size + 1));
	ft_add_garbage(0, &garbage, pwd);

	while (getcwd(pwd, size) == NULL && errno == 36)
	{
		size += 128;
		free(pwd);
		pwd = malloc(sizeof(char) * (size + 1));
		ft_add_garbage(0, &garbage, pwd);
	}
	if (getcwd(pwd, size) != NULL)
		return (getcwd(pwd, size));
	return (NULL);	
}
