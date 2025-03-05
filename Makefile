PROGRESS = \033[33m⏳\033[0m
BROOM = \033[33m🧹\033[0m
SUCCESS = \033[32m✔\033[0m

CC = cc
INCLUDES = -I./mandatory/includes
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES)

# -fsanitize=address

SRC_PATH = ./mandatory/sources/
SRC = $(SRC_PATH)main.c \
	  $(SRC_PATH)init/error.c \
	  $(SRC_PATH)init/garbage_collector.c \
	  $(SRC_PATH)init/init_all.c \
	  $(SRC_PATH)init/init_token.c \
	  $(SRC_PATH)init/signal.c \
	  $(SRC_PATH)parsing/cut_the_line.c \
	  $(SRC_PATH)parsing/quotes.c \
	  $(SRC_PATH)parsing/tokenization.c \
	  $(SRC_PATH)built-in/pwd.c \
	  $(SRC_PATH)parsing/check_parsing_error.c \
	  $(SRC_PATH)built-in/exit.c \
	  $(SRC_PATH)built-in/cd.c \
	  $(SRC_PATH)built-in/exec_bt.c \

OBJ_DIR = ./tmp
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_DIR)/%.o)
NAME = minishell

LIBFT_DIR = ./Libft
LIBFT_LIB = ./Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	@echo "\n$(PROGRESS) Compiled in progress $(PROGRESS)...\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -lreadline -o $(NAME)
	@echo "$(SUCCESS) Compiling is finished $(SUCCESS) !!!"

$(LIBFT_LIB):
	@make -s -C $(LIBFT_DIR)

clean:
	@echo "\n$(BROOM) Cleaning !!! $(BROOM)\n"
	@make -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_PATH)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/init 
	@mkdir -p $(OBJ_DIR)/parsing 
	@mkdir -p $(OBJ_DIR)/built-in

.PHONY: NAME all clean fclean re
