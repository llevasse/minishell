/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:23 by mwubneh           #+#    #+#             */
/*   Updated: 2023/08/01 15:20:03 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	false_exec(char *path, t_prompt *prompt, t_garbage *garbage)
{
	pid_t	pid;
	char	**argv;

	pid = fork();
	if (pid == -1)
		return ((void)write(2, "fork error\n", 11), exit(-1));
	else if (pid == 0)
	{
		argv = pass_args_exec(path, prompt, garbage);
		if (access(argv[0], X_OK == -1))
			return ((void) write(2, "Error, no builtin found\n", 25));
		execve(argv[0], argv, environ);
	}
	else
		wait(NULL);
}

// command like cat or grep passed without argument
// will not work if '-' is not added as argument.
// where command like ls will need PWD.
/// @brief Get arguments to pass to execve.
/// @param *path String of path to executable,
/// @param *prompt Pointer to prompt struct,
/// @param *garbage Pointer to garbage struct.
/// @return Return arguments to pass in execve.
char	**pass_args_exec(char *path, t_prompt *prompt, t_garbage *garbage)
{
	char	**argv;
	t_arg	*temp;
	int		i;

	if (!prompt->args)
	{
		argv = malloc(sizeof(char *) * 3);
		ft_add_garbage(0, &garbage, argv);
		argv[1] = "-";
		if (!ft_strcmp(prompt->cmd, "ls"))
			argv[1] = getenv("PWD");
		argv[2] = NULL;
	}
	else
	{
		argv = malloc(sizeof(char *) * (get_arg_nb(prompt->args) + 2));
		ft_add_garbage(0, &garbage, argv);
		argv[0] = ft_joinf("%s/%s", path, prompt->cmd);
		ft_add_garbage(0, &garbage, argv[0]);
		i = 0;
		temp = prompt->args;
//		printf("Cmd : |%s|\n", argv[i]);
		while (temp)
		{
			argv[i + 1] = temp->s;
//			printf("Args : |%s|\n", argv[i + 1]);
			temp = temp->next;
			i++;
		}
		argv[i + 1] = NULL;
	}
	return (argv);
}
