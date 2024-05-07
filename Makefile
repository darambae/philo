# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 12:26:12 by dabae             #+#    #+#              #
#    Updated: 2024/05/07 09:55:00 by dabae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)
CFLAGS= -Wall -Wextra -Werror
CC= cc -g -pthread

all: $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME): $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
