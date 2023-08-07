#---COMMON_VAR-----------------------------------
NAME		=	minishell
CC		=	cc
FLAGS		=	-Wall -Werror -Wextra
RM		=	rm -rf
RED		=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
NC		=	\033[0m
#---LIBFT_VAR-------------------------------------
LIBFT_PATH	=	libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(addprefix $(LIBFT_PATH), $(LIBFT_NAME))
#---MINISHELL_VAR----------------------------------
SRC		=	srcs/minishell.c \
			srcs/parsing/ft_strsep.c \
			srcs/parsing/parse.c \
			srcs/parsing/env.c \
			srcs/parsing/chars.c \
			srcs/parsing/replace_str.c \
			srcs/parsing/quotes.c \
			srcs/parsing/args/args.c \
			srcs/parsing/args/tab_utils.c \
			srcs/parsing/args/split_args.c \
			srcs/parsing/args/separate_cmd.c \
			srcs/parsing/args/wildcard.c \
			srcs/parsing/garbage_collector.c \
			srcs/parsing/direction/direction.c \
			srcs/parsing/direction/output.c \
			srcs/parsing/direction/input.c \
			srcs/parsing/direction/heredoc.c \
			srcs/parsing/export.c \
			srcs/parsing/insert_at_index.c \
			srcs/exec/exec.c \
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

$(NAME):		$(OBJS) lib norm Makefile $(HEADER)/minishell.h
				@$(CC) $(FLAGS) -g -I $(HEADER) $(OBJS) -lreadline $(LIBFT) -o $@
				@echo "$(GREEN)Minishell compiled :D$(NC)"

$(OBJS_DIR)%.o:	%.c | $(OBJS_DIR) lib Makefile $(HEADER)/minishell.h
				$(CC) $(FLAGS) -g -I $(HEADER) -c $< -o $@

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)srcs
				@mkdir -p $(OBJS_DIR)srcs/parsing
				@mkdir -p $(OBJS_DIR)srcs/parsing/args
				@mkdir -p $(OBJS_DIR)srcs/parsing/direction
				@mkdir -p $(OBJS_DIR)srcs/builtin
				@mkdir -p $(OBJS_DIR)srcs/exec

all:			$(NAME)

norm:
				@norminette $(SRC) $(HEADER) | awk '$$NF!="OK!" {print "$(RED)" $$0 "$(NC)"}'

lib:
				@echo "$(YELLOW)\nCOMPILING $(LIBFT_PATH)\n"
				@make -sC $(LIBFT_PATH)
				@echo "$(GREEN)LIBFT created\n"

clean:
				@echo "$(RED)Deleting Obj file in $(LIBFT_PATH)...\n"
				@make clean -sC $(LIBFT_PATH)
				@echo "$(GREEN)Done\n"
				@echo "$(RED)Deleting minishell object...\n"
				@$(RM) $(OBJS_DIR)
				@echo "$(GREEN)Done\n"

fclean:			clean
				@echo "$(RED)Deleting minishell executable..."
				@rm -f $(NAME)
				@make fclean -C $(LIBFT_PATH)
				@echo "$(GREEN)Done\n"

re:				fclean all

.PHONY:			all clean fclean re
