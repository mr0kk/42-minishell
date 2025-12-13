NAME = minishell

CC = cc
CFLAGS = #-Wall -Wextra -Werror

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/

SRC = main.c \
		parsing/parsing.c \
		parsing/nodes_handling.c \
		parsing/type_defining.c \
		parsing/variable_expansion.c \
		utils/utils.c \
		commands/ft_echo.c \
		pipes/pipes.c \
		errors/syntax_handling.c \
		errors/error_handling.c \
		errors/error_messages.c 


SRCS   = $(addprefix $(SRC_PATH), $(SRC))
OBJ    = $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/utils
	mkdir -p $(OBJ_PATH)/commands
	mkdir -p $(OBJ_PATH)/pipes
	mkdir -p $(OBJ_PATH)/errors
	@echo "$(BLUE)Created object directories$(NC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) $(LIBFT) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_PATH) clean
	@echo "$(RED)Object files cleaned$(NC)"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	@echo "$(RED)Executable cleaned$(NC)"

re: fclean all

.PHONY: all clean fclean re