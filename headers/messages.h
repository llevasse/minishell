/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:42:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/20 14:16:33 by llevasse         ###   ########.fr       */
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
# define PROMPT "(%d)minishell >>"
# define MEM_ERR_PROMPT "(12)minishell >>"
# define FREE_GARBAGE "Freeing %p with content %s in garbage\n"
# define ADD_GARBAGE "Adding %p with content %s to garbage\n"
# define BAD_ASS "Bad assignment\n"
# define BAD_KEY "Invalid key : %s\n"
# define BAD_ID "not a valid identifier\n"
# define W_DQUOTE "dquote>"
# define W_QUOTE "quote>"
# define ERR_PARSE_OUTPUT "Parsing error around >"
# define ERR_PARSE_INPUT "Parsing error around >"
# define ERR_OPEN_F "Error in opening file\n"
# define NO_FILE "%s : No such file or directory"
# define NO_FILE_E "No such file or directory"
# define PIPE_ERR "Error in opening pipes"
# define ERR_404 "%s: command not found\n"
# define UNEXPEC_EOF "unexpected EOF while looking for matching `%c'\n\
syntax error: unexpected end of file\n"
# define TMA "Too mane arguments\n"
# define NOT_NUM_ARG "numeric argument required\n"
#endif
