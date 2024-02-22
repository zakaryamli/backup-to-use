SRC = mandatory/main.c mandatory/parcing.c mandatory/ft_putstr_fd.c  mandatory/pipex.c mandatory/ft_split.c mandatory/ft_strchr.c  mandatory/ft_strdup.c   mandatory/ft_strjoin.c  mandatory/ft_strlcat.c mandatory/ft_strlcpy.c mandatory/ft_strlen.c mandatory/ft_strstr.c
BONUS =  bonus/main.c bonus/first_cmds.c bonus/parcing.c bonus/pipex_bonus.c bonus/ft_split.c bonus/ft_strchr.c bonus/ft_strcmp.c   bonus/ft_strdup.c   bonus/ft_strjoin.c  bonus/ft_strlcat.c bonus/ft_strlcpy.c bonus/ft_strlen.c bonus/ft_strstr.c bonus/get_next_line.c bonus/get_next_line_utils.c bonus/ft_putstr_fd.c bonus/ft_strncmp.c
OBJ = $(SRC:.c=.o)
B_OBJ = $(BONUS:.c=.o)
CC = cc 
C_FLAGS = -Wall -Wextra -Werror
NAME = pipex
B_NAME = pipex_bonus

all	:	$(NAME)

bonus : $(B_NAME)

$(NAME)	:	$(OBJ)
	$(CC)	$(C_FLAGS)	$(OBJ)	-o	$(NAME)

$(B_NAME) : $(B_OBJ)
	$(CC)	$(C_FLAGS)	$(B_OBJ)	-o	$(B_NAME)

%.o:	%.c	mandatory/pipex.h	bonus/pipex_bonus.h
	$(CC)	$(C_FLAGS)	-c	-o	$@	$<

clean :
	rm -f	$(OBJ)	$(B_OBJ)

fclean	:	clean
	rm -f	$(NAME)	$(B_NAME)

re	:	fclean	all

.PHONY : all clean fclean re bonus