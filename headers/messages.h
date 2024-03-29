/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:42:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/04 00:00:51 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define STARTUP " __    __     __     __   __     __     ______     __  __  \
   ______     __         __\n/\\ \"-./  \\   /\\ \\   /\\ \"-.\\ \\   /\\ \\   \
/\\  ___\\   /\\ \\_\\ \\   /\\  ___\\   /\\ \\       /\\ \\       \n\\ \\ \
\\-./\\ \\  \\ \\ \\  \\ \\ \\-.  \\  \\ \\ \\  \\ \\___  \\  \\ \\  __ \\  \
\\ \\  __\\   \\ \\ \\____  \\ \\ \\____ \n \\ \\_\\ \\ \\_\\  \\ \\_\\  \\ \
\\_\\\\\"\\_\\  \\ \\_\\  \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \
\\_____\\  \\ \\_____\\ \n  \\/_/  \\/_/   \\/_/   \\/_/ \\/_/   \\/_/   \
\\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/   \\/_____/ \n"
# define CTRL_C "^C\n"
# define EXIT "exit\n"
# define PROMPT "minishell >>"
# define MEM_ERR_PROMPT "minishell >>"
# define FREE_GARBAGE "Freeing %p with content %s in garbage\n"
# define ADD_GARBAGE "Adding %p with content %s to garbage\n"
# define BAD_ASS "Bad assignment\n"
# define BAD_KEY "Invalid key : %s\n"
# define BAD_ID "not a valid identifier\n"
# define W_DQUOTE "dquote>"
# define W_QUOTE "quote>"
# define ERR_PARSE_OUTPUT "Parsing error around >\n"
# define ERR_PARSE_INPUT "Parsing error around <\n"
# define ERR_OPEN_F "Error in opening file\n"
# define DENIED "Permission denied\n"
# define NO_FILE_E "No such file or directory\n"
# define PIPE_ERR "Error in opening pipes\n"
# define ERR_404 "%s: command not found\n"
# define UNEXPEC_EOF "unexpected EOF while looking for matching `"
# define UNEXPEC_PIPE "syntax error near unexpected tolen `|'\n"
# define UNEXPEC_DOC "syntax error near unexpected tolen `newline'\n"
# define TMA "Too many arguments\n"
# define NOT_NUM_ARG "numeric argument required\n"
# define ERR_QUIT "^\\QUIT (core dumped)\n"
# define ERR_PWD "pwd: %s: invalid option\npwd: usage: pwd [-LP]\n"
# define NO_HOME "HOME not set\n"
# define WARN_LVL "warning: shell level (%s) to high, resetting to 1"

#endif
