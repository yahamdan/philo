# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 01:45:42 by yahamdan          #+#    #+#              #
#    Updated: 2023/06/05 11:16:36 by yahamdan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = CC
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

 
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