# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: greed <greed@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/14 15:36:39 by greed         #+#    #+#                  #
#    Updated: 2020/06/16 11:36:00 by greed         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCS			=	main.c\
				start_exit.c\
				simple_out.c\
				get_cmd.c\
				ft_echo.c\
				cmd_dispatch.c\
				ft_exit.c\
				parse_input.c
CFILES			=	$(SRCS:%=src/%)
OFILES			=	$(CFILES:.c=.o)
CFLAGS			=	-Wall -Wextra -Werror -DNOLIST
INCLUDES		=	-I include\
					-I lib/libft\
					-I lib/liblist
LIBS			=	-L lib/libft -lft\
					-L lib/liblist -llist

# LIB LOCATIONS
LIBFT_LOC		=	lib/libft
LIBLIST_LOC		=	lib/liblist
# COLORS
WHITE   = \x1b[37;01m
CYAN    = \x1b[36;01m
PINK    = \x1b[35;01m
BLUE    = \x1b[34;01m
YELLOW  = \x1b[33;01m
GREEN   = \x1b[32;01m
RED     = \x1b[31;01m
BLACK   = \x1b[30;01m
RESET   = \x1b[0m
all: $(NAME)
$(NAME): $(OFILES)
	@echo "$(WHITE)/-----		Compiling libft		-----\\ $(RESET)"
	@make bonus -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----		Compiling liblist	-----\\ $(RESET)"
	@make -C $(LIBLIST_LOC)
	@echo "$(WHITE)/-----	Compiling minishell		-----\\ $(RESET)"
	$(CC) $(LIBS) -o $(NAME) $(OFILES)
%.o: %.c
	@gcc $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	@echo "$(WHITE)/-----		Cleaning libft		-----\\ $(RESET)"
	@make clean -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----		Cleaning liblist	-----\\ $(RESET)"
	@make clean -C $(LIBLIST_LOC)
	@echo "$(WHITE)/-----	Cleaning minishell		-----\\ $(RESET)"
	rm -f $(OFILES)
fclean: clean
	@echo "$(WHITE)/-----		Fcleaning libft		-----\\ $(RESET)"
	make fclean -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----		Fcleaning liblist	-----\\ $(RESET)"
	make fclean -C $(LIBLIST_LOC)
	@echo "$(WHITE)/-----	Fcleaning minishell		-----\\ $(RESET)"
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
