CC = cc

CFLAGS = -Wall -Wextra -Werror -g -O0

INCLUDE = -I./includes

LIBFT_DIR = ./libft/
LIBFT_SRC = $(LIBFT_DIR)ft_atoi.c \
			$(LIBFT_DIR)ft_bzero.c \
			$(LIBFT_DIR)ft_calloc.c \
			$(LIBFT_DIR)ft_isalnum.c \
			$(LIBFT_DIR)ft_isalpha.c \
			$(LIBFT_DIR)ft_isascii.c \
			$(LIBFT_DIR)ft_isdigit.c \
			$(LIBFT_DIR)ft_isprint.c \
			$(LIBFT_DIR)ft_itoa.c \
			$(LIBFT_DIR)ft_lstadd_back.c \
			$(LIBFT_DIR)ft_lstadd_front.c \
			$(LIBFT_DIR)ft_lstclear.c \
			$(LIBFT_DIR)ft_lstdelone.c \
			$(LIBFT_DIR)ft_lstiter.c \
			$(LIBFT_DIR)ft_lstlast.c \
			$(LIBFT_DIR)ft_lstmap.c \
			$(LIBFT_DIR)ft_lstnew.c \
			$(LIBFT_DIR)ft_lstsize.c \
			$(LIBFT_DIR)ft_memchr.c \
			$(LIBFT_DIR)ft_memcmp.c \
			$(LIBFT_DIR)ft_memcpy.c \
			$(LIBFT_DIR)ft_memmove.c \
			$(LIBFT_DIR)ft_memset.c \
			$(LIBFT_DIR)ft_putchar_fd.c \
			$(LIBFT_DIR)ft_putendl_fd.c \
			$(LIBFT_DIR)ft_putnbr_fd.c \
			$(LIBFT_DIR)ft_putstr_fd.c \
			$(LIBFT_DIR)ft_split.c \
			$(LIBFT_DIR)ft_strchr.c \
			$(LIBFT_DIR)ft_strcmp.c \
			$(LIBFT_DIR)ft_strdup.c \
			$(LIBFT_DIR)ft_striteri.c \
			$(LIBFT_DIR)ft_strjoin.c \
			$(LIBFT_DIR)ft_strlcat.c \
			$(LIBFT_DIR)ft_strlcpy.c \
			$(LIBFT_DIR)ft_strlen.c \
			$(LIBFT_DIR)ft_strmapi.c \
			$(LIBFT_DIR)ft_strncmp.c \
			$(LIBFT_DIR)ft_strnstr.c \
			$(LIBFT_DIR)ft_strrchr.c \
			$(LIBFT_DIR)ft_strtrim.c \
			$(LIBFT_DIR)ft_substr.c \
			$(LIBFT_DIR)ft_tolower.c \
			$(LIBFT_DIR)ft_toupper.c

FT_PRINTF_DIR = ./ft_printf/
FT_PRINTF_SRC = $(FT_PRINTF_DIR)ft_print_hex.c \
				$(FT_PRINTF_DIR)ft_print_pointer.c \
				$(FT_PRINTF_DIR)ft_print_unsigned.c \
				$(FT_PRINTF_DIR)ft_printchar.c \
				$(FT_PRINTF_DIR)ft_printf.c \
				$(FT_PRINTF_DIR)ft_printnbr.c \
				$(FT_PRINTF_DIR)ft_printpercent.c \
				$(FT_PRINTF_DIR)ft_printstr.c

GNL_DIR = ./GNL/
GNL_SRC	=	$(GNL_DIR)get_next_line_utils.c \
			$(GNL_DIR)get_next_line.c

SRC = $(LIBFT_SRC) $(FT_PRINTF_SRC) $(GNL_SRC)

OBJ = $(SRC:.c=.o)

NAME = libft.a

AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re