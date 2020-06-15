# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: greed <greed@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 10:31:09 by greed         #+#    #+#                  #
#    Updated: 2020/05/17 20:40:04 by greed         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
SRCS		=	ft_atoi ft_isalnum ft_isalpha ft_isascii\
	ft_isdigit ft_isprint ft_memset ft_strchr ft_strlcat ft_strlcpy ft_strlen\
	ft_strncmp ft_strnstr ft_strrchr ft_tolower ft_toupper ft_bzero ft_memcpy\
	ft_memccpy ft_memchr ft_memcmp ft_memmove ft_calloc ft_strdup ft_substr\
	ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_putchar_fd\
	ft_putstr_fd ft_putendl_fd ft_putnbr_fd get_next_line\
	ft_printf ft_print_func ft_helper ft_flag_func\
	ft_print_num ft_uint ft_x ft_sizes_num ft_function_links\
	ft_sizes_x ft_llu ft_pointer get_next_line_utils ft_strcmp
B_SRCS		=	ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus\
	ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus\
	ft_lstiter_bonus ft_lstmap_bonus
CFILES		=	$(SRCS:%=%.c)
OFILES		=	$(CFILES:.c=.o)
BFILES		=	$(B_SRCS:%=%.c)
BOFILES		=	$(BFILES:.c=.o)
FLAGS		=	-Wall -Werror -Wextra -g

# COLORS
PINK	= \x1b[35;01m
BLUE	= \x1b[34;01m
YELLOW	= \x1b[33;01m
GREEN	= \x1b[32;01m
RED		= \x1b[31;01m
RESET	= \x1b[0m

all: $(NAME)

$(NAME): $(OFILES)
	@echo "$(YELLOW)Linking the library"
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)
	@echo "$(GREEN)Done"

%.o: %.c
	@echo "$(BLUE)Compiling: $<"
	@gcc -o $@ -c $< $(FLAGS)

clean: clean_b
	@echo "$(RED) Cleaning..."

fclean: clean_b
	@echo "$(PINK)Fabulous cleaning..."
	@rm -f $(NAME)

clean_b:
	@rm -f $(BOFILES)
	@rm -f $(OFILES)

re: fclean all

bonus: $(OFILES) $(BOFILES) $(NAME)
	@echo "$(YELLOW)Linking the bonusses into the library"
	@ar rc $(NAME) $(OFILES) $(BOFILES)
	@ranlib $(NAME)
	@echo "$(GREEN)Done"
