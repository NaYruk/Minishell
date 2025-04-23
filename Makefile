PROGRESS = \033[33m⏳\033[0m
BROOM = \033[33m🧹\033[0m
SUCCESS = \033[32m✔\033[0m

CC = cc
INCLUDES = -I./mandatory/includes -I/opt/homebrew/opt/readline/include
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES)

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
	  $(SRC_PATH)parsing/check_rafter.c \
	  $(SRC_PATH)parsing/check_pipes.c \
	  $(SRC_PATH)parsing/is_operator.c \
	  $(SRC_PATH)parsing/replace_dollars.c \
	  $(SRC_PATH)parsing/escaped_char.c \
	  $(SRC_PATH)parsing/expand.c \
	  $(SRC_PATH)built-in/pwd.c \
	  $(SRC_PATH)built-in/exit.c \
	  $(SRC_PATH)built-in/cd.c \
	  $(SRC_PATH)built-in/env.c \
	  $(SRC_PATH)built-in/echo.c \
	  $(SRC_PATH)built-in/unset.c \
	  $(SRC_PATH)built-in/export.c \
	  $(SRC_PATH)built-in/print_export.c \
	  $(SRC_PATH)built-in/utils_bt.c \
	  $(SRC_PATH)built-in/utils_export.c \
	  $(SRC_PATH)exec/exec_command/execution.c \
	  $(SRC_PATH)exec/exec_command/execution2.c \
	  $(SRC_PATH)exec/exec_command/exec_builtin.c \
	  $(SRC_PATH)exec/exec_command/exec_cmd.c \
	  $(SRC_PATH)exec/exec_command/heredoc.c \
	  $(SRC_PATH)exec/exec_command/heredoc2.c \
	  $(SRC_PATH)exec/exec_command/attribute_redirections.c \
	  $(SRC_PATH)exec/exec_command/exec_utils.c \
	  $(SRC_PATH)exec/exec_command/waiting_process.c \
	  $(SRC_PATH)exec/setup_execution/set_exec_struct.c \
	  $(SRC_PATH)exec/setup_execution/get_cmd_path.c \
	  $(SRC_PATH)exec/setup_execution/get_args.c \
	  $(SRC_PATH)exec/setup_execution/set_redirections.c \
	  $(SRC_PATH)exec/setup_execution/validity_path.c \
	  $(SRC_PATH)exec/setup_execution/redir_chained_list.c \

OBJ_DIR = ./tmp
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_DIR)/%.o)
NAME = minishell

LIBFT_DIR = ./Libft
LIBFT_LIB = ./Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	@echo "\n$(PROGRESS) Compiled in progress $(PROGRESS)...\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -L/opt/homebrew/opt/readline/lib -lreadline -o $(NAME)
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
	@mkdir -p $(OBJ_DIR)/exec
	@mkdir -p $(OBJ_DIR)/exec/exec_command
	@mkdir -p $(OBJ_DIR)/exec/setup_execution

.PHONY: NAME all clean fclean re
