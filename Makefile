NAME = minishell

SRC_PATH = ./src/
OBJS_PATH = ./objs/

SRC = $(SRC_PATH)main.c $(SRC_PATH)echo.c $(SRC_PATH)utils.c $(SRC_PATH)split.c $(SRC_PATH)builtins.c
OBJS = $(SRC:$(SRC_PATH)%.c=$(OBJS_PATH)%.o)

# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
CFLAGS = -Wall -Werror -Wextra -g

CC = cc


%.o: %.c
		$(CC) -c $< -o $@

$(NAME): $(OBJS)
		@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -lreadline

$(OBJS_PATH)%.o: $(SRC_PATH)%.c | $(OBJS_PATH)
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(OBJS_PATH):
		mkdir -p $(OBJS_PATH)

valgrind_supp: all
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp ./$(NAME)

.PHONY: all clean fclean re
