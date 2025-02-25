GREEN = \033[32m
CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m

CC = cc 
INCLUDES = -I./mandatory/includes
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

SRC_PATH = ./mandatory/sources/
SRC = $(SRC_PATH)main.c

OBJ = $(SRC:.c=.o)
NAME = minishell

LIBFT_DIR = ./Libft
LIBFT_LIB = ./Libft/libft.a

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
		@echo "\n$(CYAN)Starting compilation...$(RESET)\n"
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME)
		@echo "\n$(GREEN)Compilation of Minishell project is complete.$(RESET)\n"

$(LIBFT_LIB):
			@echo "Compiling Libft..."
			@make -C $(LIBFT_DIR)
			@echo "Libft Successfully compiled !\n"

clean: 
	   @echo "Cleaning $(YELLOW)Minishell$(RESET) object files..."
	   @rm -rf $(OBJ_PATH)
	   @echo "Cleaning $(YELLOW)Minishell$(RESET) object files is FINISH"

fclean: 
		@echo "\n$(GREEN)Cleaning all...\n$(RESET)"
		@echo "Cleaning $(YELLOW)Minishell$(RESET) object files..."
	    @rm -rf $(OBJ_PATH)
	    @echo "Cleaning $(YELLOW)Minishell$(RESET) object files is FINISH"
		@rm -rf $(NAME)
		@echo "Cleaning $(YELLOW)Executable$(RESET) file..."
		@echo "Cleaning $(YELLOW)Executable$(RESET) file is FINISH"


re: fclean all

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re