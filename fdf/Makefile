SRC = mandatory/fdf.c mandatory/ft_atoi.c  mandatory/ft_strlcpy.c  mandatory/get_next_line_utils.c mandatory/parcing.c mandatory/ft_split.c mandatory/get_next_line.c mandatory/ft_atoi_base.c
BONUS = bonus/fdf_bonus.c bonus/ft_atoi.c  bonus/ft_strlcpy.c  bonus/get_next_line_utils.c bonus/parcing.c bonus/ft_split.c bonus/get_next_line.c bonus/ft_atoi_base.c
OBJS = $(SRC:.c=.o)
B_OBJ = $(BONUS:.c=.o)
CC = cc 
C_FLAGS = -Wall -Wextra -Werror	-I	/usr/local/include	-L	/usr/local/lib	-lmlx	-framework	OpenGL	-framework	AppKit
NAME = fdf
B_NAME = fdf_bonus

all: $(NAME)

bonus : $(B_NAME)

clean:
	rm -rf $(OBJS) $(B_OBJ)

fclean: clean
	rm -rf $(NAME) $(B_NAME)

re: fclean all

mandatory/%.o: mandatory/%.c mandatory/fdf.h
	$(CC)	-Wall -Wextra -Werror	-c	$<	-o	$@

bonus/%.o: bonus/%.c bonus/fdf_bonus.h
	$(CC)	-Wall -Wextra -Werror	-c	$<	-o	$@

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -o $(NAME)

$(B_NAME) : $(B_OBJ)
	$(CC) $(C_FLAGS) $(B_OBJ) -o $(B_NAME)

.PHONY : all clean fclean re