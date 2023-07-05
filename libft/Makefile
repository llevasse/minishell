# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwubneh <alphom@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 15:59:41 by mwubneh           #+#    #+#              #
#    Updated: 2022/12/17 18:01:24 by mwubneh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#---COMMON_VAR-----------------------------------
NAME		=	libft.a
CC			=	cc
FLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
OBJS_DIR	=	.OBJS/
#---LIBFT_VAR-----------------------------------
SRC_PART = 	ft_isalpha.c\
			ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_strlen.c\
			ft_memset.c\
			ft_bzero.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_strlcpy.c\
			ft_strlcat.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strncmp.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_strnstr.c\
			ft_atoi.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
			ft_lstadd_back.c\
			ft_lstadd_front.c\
			ft_lstclear.c\
			ft_lstdelone.c\
			ft_lstiter.c\
			ft_lstlast.c \
			ft_lstmap.c\
			ft_lstnew.c\
			ft_lstsize.c
OBJS_DIR	=	.OBJS_libft/
OBJS_MAND	=	$(addprefix $(OBJS_DIR), $(SRC_PART:.c=.o))
HEADER		=	libft.h
#---RULES----------------------------------------

all:			$(NAME)

$(NAME):		$(OBJS_MAND)
				ar -rcs $(NAME) $(OBJS_MAND)


$(OBJS_DIR)%.o:	%.c | $(OBJS_DIR)
				$(CC) -c $< -o $@

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)get_next_line

clean:
				$(RM) $(OBJS_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean re fclean
