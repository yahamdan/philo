# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 01:45:42 by yahamdan          #+#    #+#              #
#    Updated: 2023/04/13 03:40:45 by yahamdan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = CC

# CFLAGS = -fsanitize=thread -g3
 
SRC = philo.c ft_atoi.c

OBG = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBG)
	$(CC) $(CFLAGS) -g -pthread -o $(NAME) $(OBG)

clean :
	rm -rf $(OBG)

fclean : clean
	rm -rf $(NAME)

re : fclean all 