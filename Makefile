# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 17:58:34 by youhan            #+#    #+#              #
#    Updated: 2022/11/07 20:38:37 by youhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = miniRT
CFLAGS = -Wall -Werror -Wextra
CFLAG = -Lmlx -lmlx -framework OpenGL -framework AppKit
SRCS = $(addprefix parsing/, ft_char_double.c ft_split.c get_next_line.c \
							get_next_line_utils.c check_input.c push_object1.c \
							push_object2.c push_object3.c push_object4.c \
							push_data1.c push_data2.c utils1.c utils2.c) \
		$(addprefix utils/, ft_math.c ft_math_vector1.c ft_math_vector2.c \
							ft_utils.c init_mlx_data.c mlx_init.c axis.c) \
		$(addprefix rotate/, copy_data.c rotate_init.c rotate_utils.c rotate.c \
							 updata_rot.c) \
		$(addprefix axis_uv/, normal_vec.c find_uv_cn.c find_uv_cy.c \
							  find_uv_pl.c find_uv_sp.c) \
		$(addprefix hit/, hit_cn.c hit_cy.c hit_cn_utils.c hit_cy_utils.c \
						  hit_pl.c hit_sp.c color_select.c view_vector.c) \
		$(addprefix ray_tracer/, phong_init.c phong_reflection.c gray_cn.c gray_cy.c \
								 gray_sp_pl.c phong_utils.c)
SRCS_MAIN = main.c
SRCS_BONUS = bonus/main_bonus.c
MLX = libmlx.a
OBJS = ${SRCS:.c=.o}
MAIN_OBJ = ${SRCS_MAIN:.c=.o}
BONUS_OBJS = ${SRCS_BONUS:.c=.o}

ifdef FLAG_BONUS
	OBJ = ${OBJS} ${BONUS_OBJS}
else
	OBJ = ${OBJS} ${MAIN_OBJ}
endif

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@
	
${NAME} : ${OBJ} ${MLX}
	${CC} ${CFLAG} ${CFLAGS} -o ${NAME} ${OBJ} ${MLX}

${MLX} : 
	make -C mlx
	cp mlx/${MLX} ./

all : ${NAME}

clean :
	rm -f ${OBJS} ${MLX} ${MAIN_OBJ} ${BONUS_OBJS}
	make clean -C mlx

fclean:
	make clean
	rm -f ${NAME}

re:
	make fclean
	make all

bonus :
	make FLAG_BONUS=1 all

.PHONY : all clean fclean re bonus