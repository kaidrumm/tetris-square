# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdrumm <kdrumm@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/15 13:23:47 by dbotova           #+#    #+#              #
#    Updated: 2016/10/27 15:53:26 by kdrumm           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = fillit
CFLAGS = -Wall -Wextra -Werror
SRC_NAME = fillit.c fillit2.c fillit3.c fillit4.c
OBJ_NAME = $(SRC_NAME:.c=.o)

.PHONY: clean fclean re

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC_NAME) -L. -lft

norme:
	norminette $(SRC_NAME)

clean:
	rm -f $(OBJ_NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

