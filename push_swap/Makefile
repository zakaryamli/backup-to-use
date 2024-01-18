SRC = parcing.c push_swap.c instructions_a.c instructions_b.c main.c sort_three_five.c ft_atoi.c ft_split.c ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_check_dup.c ft_extractor.c  ft_free_leaks.c ft_protection.c  ft_finder.c  
OBJS = $(SRC:.c=.o)
CC = cc 
C_FLAGS = -Wall -Wextra -Werror
NAME = push_swap

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

%.o: %.c push_swap.h
	$(CC) $(C_FLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
