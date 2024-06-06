# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 15:12:03 by zyamli            #+#    #+#              #
#    Updated: 2024/06/06 16:18:04 by zyamli           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  mandatory/main.c mandatory/utils.c mandatory/actions.c mandatory/assing_handler.c mandatory/dinner_time.c mandatory/parsing.c mandatory/posix_stuff.c mandatory/time.c mandatory/value_handler.c
BONUS =  bonus/main.c bonus/utils.c bonus/actions.c bonus/dinner_time.c bonus/parsing.c bonus/posix_stuff.c bonus/time.c
OBJ = $(SRC:.c=.o)
B_OBJ = $(BONUS:.c=.o)
CC = cc
C_FLAGS = -Wall -Wextra -Werror
NAME = philo
B_NAME = philo_bonus

all	:	$(NAME)

bonus : $(B_NAME)

$(NAME)	:	$(OBJ)
	$(CC)	$(C_FLAGS)	$(OBJ)	-o	$(NAME)

$(B_NAME) : $(B_OBJ)
	$(CC)	$(C_FLAGS)	$(B_OBJ)	-o	$(B_NAME)

%.o:	%.c	mandatory/philo.h	bonus/philo_bonus.h
	$(CC)	$(C_FLAGS)	-c	-o	$@	$<

clean :
	rm -f	$(OBJ)	$(B_OBJ)

fclean	:	clean
	rm -f	$(NAME)	$(B_NAME)

re	:	fclean	all

.PHONY : clean