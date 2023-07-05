#---COMMON_VAR-----------------------------------
NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
#---LIBFT_VAR-------------------------------------
LIBFT_PATH	=	libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(addprefix $(LIBFT_PATH), $(LIBFT_NAME))
#---MINISHELL_VAR----------------------------------
SRC			=
OBJS_DIR	=	.OBJS/
OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER		=
#---RULES----------------------------------------

all:			$(NAME)

lib:
				@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)\n"
				@make -C $(LIBFT_PATH)
				@echo "\033[1;32mLIBFT_lib created\n"

$(OBJS_DIR)%.o:	%.c | $(OBJS_DIR)
				$(CC) $(FLAGS) -c $< -o $@

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)

clean:
				@echo "\033[0;31mDeleting Obj file in $(LIBFT_PATH)...\n"
				@make clean -sC $(LIBFT_PATH)
				@echo "\033[1;32mDone\n"
				@echo "\033[0;31mDeleting minishell object...\n"
				@$(RM) $(OBJS_DIR)
				@echo "\033[1;32mDone\n"

fclean:			clean
				@echo "\033[0;31mDeleting minishell executable..."
				@rm -f $(NAME)
				@make fclean -C $(LIBFT_PATH)
				@echo "\033[1;32mDone\n"

re:				fclean all

.PHONY:			all clean fclean re
