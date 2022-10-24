# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 17:58:34 by youhan            #+#    #+#              #
#    Updated: 2022/10/24 20:59:22 by youhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g
NAME = a.out
CFLAGS = -Wall -Werror -Wextra
CFLAG = -Lmlx -lmlx -framework OpenGL -framework AppKit
SRCS = main.c char_double.c get_next_line.c get_next_line_utils.c mlx_init.c triangle.c utils.c print.c
MLX = libmlx.a
OBJS = ${SRCS:.c=.o}

.o : .c
	${CC} ${CFLAGS} -c $< -o $@
	
${NAME} : ${OBJS} ${MLX}
	${CC} ${CFLAG} ${CFLAGS} -o ${NAME} ${OBJS} ${MLX}

${MLX} : 
	make -C mlx
	cp mlx/${MLX} ./

all : ${NAME}

clean :
	rm -f ${OBJS} ${MLX}
	make clean -C mlx
fclean: clean
	rm -f ${NAME}
	

re: fclean all

.PHONY : all clean fclean re