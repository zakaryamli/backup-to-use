# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 15:12:03 by zyamli            #+#    #+#              #
#    Updated: 2024/06/06 19:13:39 by zyamli           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  main.c utils.c actions.c assing_handler.c dinner_time.c parsing.c posix_stuff.c time.c value_handler.c
OBJ = $(SRC:.c=.o)
CC = cc
C_FLAGS = -Wall -Wextra -Werror
NAME = philo

all	:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC)	$(C_FLAGS)	$(OBJ)	-o	$(NAME)

%.o:	%.c	philo.h
	$(CC)	$(C_FLAGS)	-c	-o	$@	$<

clean :
	rm -f	$(OBJ)

fclean	:	clean
	rm -f	$(NAME)

re	:	fclean	all

.PHONY : clean