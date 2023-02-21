# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 17:41:06 by aahrach           #+#    #+#              #
#    Updated: 2023/02/21 17:52:16 by aahrach          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c philo.c ft_atoi.c 

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all = $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) #-fsanitize=thread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all