NAME = pipex

SRC = $(addsuffix .c, main utils errors checks)

OBJ := $(SRC:%.c=%.o)

CC = gcc
CCFLAGS = -Werror -Wall -Wextra
RM = rm -f
LIB = -C libft

all: $(NAME)
$(NAME): $(OBJ)
	@make $(LIB)
	$(CC) $^ -Llibft -lft -o $(NAME)

libft:
	@make $(LIB)/

%.o: %.c
	$(CC) $(CCFLAGS) -Iincludes -Ilibft -c $< -o $@

clean:
	$(RM) $(OBJ)
	make clean $(LIB)/
	
fclean: clean
	$(RM) $(NAME)
	make fclean $(LIB)/

re: fclean all

debug: $(OBJ)
	$(CC) $(CCFLAGS) -fsanitize=address -Llibft -lft $^ -o $(NAME)

.PHONY: libft test
