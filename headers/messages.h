/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:42:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/11 15:06:06 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_S

# define CTRL_C "^C\n"
# define EXIT "exit\n"
# define PROMPT "(%d)minishell >>"
# define MEM_ERR_PROMPT "minishell >>"
# define FREE_GARBAGE "Freeing %p with content %s in garbage\n"
# define ADD_GARBAGE "Adding %p with content %s to garbage\n"
# define BAD_ASS "Bad assignment\n"
# define BAD_KEY "Invalid key : %s\n"
# define W_DQUOTE "dquote>"
# define W_QUOTE "quote>"
# define ERR_PARSE_OUTPUT "Parsing error around >\n"
# define ERR_PARSE_INPUT "Parsing error around >\n"
# define ERR_OPEN_F "Error in opening file\n"
# define NO_FILE "%s : No suche file or directory\n"
# define PIPE_ERR "Error in opening pipes\n"
#endif
