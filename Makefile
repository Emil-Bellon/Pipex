# **************************************************************************** #
#	                                                                          #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/17 13:38:53 by ebellon           #+#    #+#              #
#    Updated: 2021/06/17 13:41:22 by ebellon          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME					= pipex
FILES					=

INC_FILES				= pipex.h
INC_PATH				= ./Headers/
INC							 = $(addprefix ${INC_PATH}, ${INC_FILES})
SRC_PATH				= ./Srcs/
SRC							 = $(addprefix ${SRC_PATH}, ${FILES})

CC							  = gcc
OBJS					= ${SRC:.c=.o}
FLAGS					= -Wall -Wextra -Werror

#LIBRARY
NAME_LIBFT				= libft.a
LIBFT_PATH				= libft/
LIBFT					= $(addprefix ${LIBFT_PATH}, ${NAME_LIBFT})

all:					${NAME}

# linking
${NAME}:				lib ${OBJS}
								${CC} ${OBJS} main.c -o ${NAME} ${NAME_LIBFT} ${NAME_MINILIBX} -I ${INC_PATH} $(FLAGS)

%.o: %.c				${INC}
								${CC} -c $< -o $@ -I ${INC_PATH} ${FLAGS}

# source compilation
lib:
								make -C ${LIBFT_PATH}
								cp ${LIBFT} .


clean:
								make -C ${LIBFT_PATH} clean
								${RM} ${OBJS}
								${RM} pipex.bmp

fclean:	clean
								${RM} ${NAME}
								${RM} ${LIBFT}
								${RM} ${NAME_LIBFT}
								${RM} ${MINILIBX}

re:		fclean all


.PHONY: all clean fclean re bonus lib