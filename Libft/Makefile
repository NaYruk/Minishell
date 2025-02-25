GREEN = \033[32m
CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m

CC = cc

CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)

INCLUDE = -I./includes

SRC_PF = ./ft_printf/
SRC_GNL = ./get_next_line/
SRC_LIB = ./libft/
SRC = $(SRC_PF)ft_printf.c $(SRC_PF)print_char_or_string.c $(SRC_PF)print_hexa.c $(SRC_PF)print_ptr.c $(SRC_PF)print_unsigned_decimal.c \
		$(SRC_GNL)get_next_line.c $(SRC_GNL)get_next_line_utils.c \
		$(SRC_LIB)ft_atoi.c $(SRC_LIB)ft_atoll.c $(SRC_LIB)ft_bzero.c $(SRC_LIB)ft_calloc.c $(SRC_LIB)ft_isalnum.c $(SRC_LIB)ft_isalpha.c $(SRC_LIB)ft_isascii.c $(SRC_LIB)ft_isdigit.c $(SRC_LIB)ft_isprint.c $(SRC_LIB)ft_itoa.c $(SRC_LIB)ft_lstadd_back.c \
		$(SRC_LIB)ft_lstadd_front.c $(SRC_LIB)ft_lstclear.c $(SRC_LIB)ft_lstdelone.c $(SRC_LIB)ft_lstiter.c $(SRC_LIB)ft_lstlast.c $(SRC_LIB)ft_lstmap.c $(SRC_LIB)ft_lstnew.c $(SRC_LIB)ft_lstsize.c $(SRC_LIB)ft_memchr.c $(SRC_LIB)ft_memcmp.c $(SRC_LIB)ft_memcpy.c \
		$(SRC_LIB)ft_memmove.c $(SRC_LIB)ft_memset.c $(SRC_LIB)ft_putchar_fd.c $(SRC_LIB)ft_putendl_fd.c $(SRC_LIB)ft_putnbr_fd.c $(SRC_LIB)ft_putstr_fd.c $(SRC_LIB)ft_split.c $(SRC_LIB)ft_strchr.c $(SRC_LIB)ft_strdup.c $(SRC_LIB)ft_striteri.c $(SRC_LIB)ft_strjoin.c \
		$(SRC_LIB)ft_strlcat.c $(SRC_LIB)ft_strlcpy.c $(SRC_LIB)ft_strlen.c $(SRC_LIB)ft_strmapi.c $(SRC_LIB)ft_strncmp.c $(SRC_LIB)ft_strnstr.c $(SRC_LIB)ft_strrchr.c $(SRC_LIB)ft_strtrim.c $(SRC_LIB)ft_substr.c $(SRC_LIB)ft_tolower.c $(SRC_LIB)ft_toupper.c \
		
OBJ = $(SRC:.c=.o)

NAME = libft.a

AR = ar -r -c -s

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n$(CYAN)Archiving Libft functions into $(NAME)...$(RESET)\n"
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)Libft archive created :$(RESET) $(YELLOW)$(NAME)$(RESET)\n"

$(OBJ): %.o: %.c
		@echo "Compiling $<"
		@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: bonus clean fclean re

clean:
	@echo "Cleaning $(YELLOW)Libft$(RESET) object files..."
	@rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all