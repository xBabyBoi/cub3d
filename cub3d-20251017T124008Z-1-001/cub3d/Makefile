NAME = cub3D

SRC = main.c \
	map_parsing.c \
	map_validation.c \
	map_info.c \
	utils.c \
	ft_strtrim.c \
	ft_itoa.c \
	Get_next_line/get_next_line.c \
	Get_next_line/get_next_line_utils.c
          
OBJS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re%