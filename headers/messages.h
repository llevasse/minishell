/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:42:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/11 17:29:30 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define CTRL_C "^C"
# define EXIT "exit\n"
# define PROMPT "\n(%d)minishell >>"
# define MEM_ERR_PROMPT "(12)minishell >>"
# define FREE_GARBAGE "Freeing %p with content %s in garbage"
# define ADD_GARBAGE "Adding %p with content %s to garbage"
# define BAD_ASS "Bad assignment"
# define BAD_KEY "Invalid key : %s"
# define W_DQUOTE "dquote>"
# define W_QUOTE "quote>"
# define ERR_PARSE_OUTPUT "Parsing error around >"
# define ERR_PARSE_INPUT "Parsing error around >"
# define ERR_OPEN_F "Error in opening file"
# define NO_FILE "%s : No suche file or directory"
# define PIPE_ERR "Error in opening pipes"
#endif
