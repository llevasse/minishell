/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:41:19 by llevasse          #+#    #+#             */
/*   Updated: 2023/07/31 17:24:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_for_wildcard(t_prompt *prompt, char **arg, t_garbage *garbage)
{
	char	*pwd;

	pwd = get_pwd(garbage);
	printf("Wildcard : %s\n", pwd);
	(void)arg;
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
