# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 17:04:53 by dabae             #+#    #+#              #
#    Updated: 2024/05/13 09:46:39 by dabae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)
CFLAGS= -Wall -Wextra -Werror
CC= cc -g -pthread

#Checking data race
#CC= cc -g -pthread -fsanitize=thread

all: $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME): $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re