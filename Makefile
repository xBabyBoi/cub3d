# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 21:45:03 by yel-qori          #+#    #+#              #
#    Updated: 2025/10/09 11:23:33 by yel-qori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
SRC = main.c\
	draw_map.c\
	get_next_line_utils.c\
	get_next_line.c\
	helper_functions.c\
	keys_handler.c\
	movements.c\
	raycasting.c\
	
OBJS = ${SRC:.c=.o}

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${OBJS} ${LDFLAGS} -o ${NAME}



clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re