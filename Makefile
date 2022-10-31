# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 17:58:34 by youhan            #+#    #+#              #
#    Updated: 2022/11/01 01:17:18 by chanhyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g
NAME = miniRT
CFLAGS = -Wall -Werror -Wextra
CFLAG = -Lmlx -lmlx -framework OpenGL -framework AppKit
SRCS = $(addprefix parsing/, ft_char_double.c ft_split.c get_next_line.c get_next_line_utils.c \
							check_input.c push_a.c push_rgb.c) \
		$(addprefix utils/, utils1.c utils2.c) \
mlx_init.c utils.c print.c main.c 
MLX = libmlx.a
OBJS = ${SRCS:.c=.o}

%.o : %.c
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
fclean:
	make clean
	rm -f ${NAME}
	

re:
	make fclean
	make all

.PHONY : all clean fclean re-