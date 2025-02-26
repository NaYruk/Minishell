PROGRESS = \033[33m⏳\033[0m
BROOM = \033[33m🧹\033[0m
SUCCESS = \033[32m✔\033[0m

CC = cc 
INCLUDES = -I./mandatory/includes
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES)

# -fsanitize=address 

SRC_PATH = ./mandatory/sources/
SRC = $(SRC_PATH)main.c \
	  $(SRC_PATH)init/init_all.c \
	  $(SRC_PATH)init/garbage_collector.c \

OBJ = $(SRC:.c=.o)
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
	   @rm -rf $(OBJ)

fclean: clean
		@make -s -C $(LIBFT_DIR) fclean
		@rm -rf $(NAME)

re: fclean all

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re