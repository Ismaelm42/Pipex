# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 14:07:25 by imoro-sa          #+#    #+#              #
#    Updated: 2023/03/22 14:07:28 by imoro-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c	pipex_utils.c

OBJT = $(SRC:.c=.o)

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

MAKEFLAGS += --quiet

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C ./libft

$(NAME): $(LIBFT) $(OBJT)
	${CC} $(CFLAGS) $(SRC) $(LIBFT) -o ${NAME}

clean:
	$(RM) $(OBJT)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean
	$(RM) ./pipex
	$(RM) ./outfile
#eliminar dos reglas finales.

re: fclean all
	make clean
#eliminar make clean para la entrega.

.PHONY : all clean fclean re
