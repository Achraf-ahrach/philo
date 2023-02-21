# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 19:15:01 by aahrach           #+#    #+#              #
#    Updated: 2023/02/21 17:50:35 by aahrach          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS = philo_bonus

SRC_BONUS = ./Bonus/philo_bonus

OBJ_BONUS = $(SRC_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all = $(NAME_BONUS)

$(NAME_BONUS) = $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

clean:
	rm -f $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME_BONUS)

re: fclean all