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
SRC		=	srcs/minishell.c \
			srcs/parsing/ft_strsep.c \
			srcs/parsing/parse.c \
			srcs/builtin/ft_echo.c \
			srcs/builtin/ft_env.c \
			srcs/builtin/ft_unset.c \
			srcs/builtin/ft_exit.c \
			srcs/builtin/ft_pwd.c \
			srcs/builtin/ft_export.c \
			srcs/builtin/ft_cd.c \

OBJS_DIR	=	.OBJS/
OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER		=	headers
#---RULES----------------------------------------

$(NAME):		$(OBJS) 
				$(CC) $(FLAGS) -g -I $(HEADER) $(OBJS) -lreadline $(LIBFT) -o $@
				@echo "$(GREEN)Minishell compiled :D$(NC)"
				@norminette $(FILES) $(HEADER) | awk '$$NF!="OK!" {print "$(RED)" $$0 "$(NC)"}'


$(OBJS_DIR)%.o:	%.c | $(OBJS_DIR) lib
				$(CC) $(FLAGS) -g -I $(HEADER) -c $< -o $@

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)srcs
				@mkdir -p $(OBJS_DIR)srcs/parsing
				@mkdir -p $(OBJS_DIR)srcs/builtin

all:			$(NAME)

lib:
				@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)\n"
				@make -sC $(LIBFT_PATH)
				@echo "\033[1;32mLIBFT_lib created\n"

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
