# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/06 19:40:25 by mle-roy           #+#    #+#              #
#    Updated: 2014/03/06 19:40:25 by mle-roy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=lem_in_gh
VERSION=1.0.7
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./libft/includes
LIBS=-L ./libft -l ft

SRC=add_connex.c \
	add_room.c \
	add_start_end_ant.c \
	debug_print_lem.c \
	find_solution.c \
	get_lex.c \
	get_maze.c \
	lem_lex_init.c \
	main.c \
	move_ants.c \
	print_result.c \
	save_solution.c \
	treat_maze.c \

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c lemmin.h ./libft/includes
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))
	@($(MAKE) -C ./libft fclean)

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\033[32m$(NAME)\033[00m]")

.PHONY: all build clean fclean re v

