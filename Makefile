NAME = minishell

CC = cc
CFLAGS = #-Wall -Wextra -Werror

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/

SRC = main.c \
		parsing/parsing.c

SRCS   = $(addprefix $(SRC_PATH), $(SRC))
OBJ    = $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

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

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re