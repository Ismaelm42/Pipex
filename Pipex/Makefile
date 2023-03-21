NAME = pipex

LIBFT = ./Libft/

SRC = pipex.c 

OBJT = $(SRC:.c=.o)

CC = gcc

MAKEFLAGS += --quiet

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

RM = rm -f

COLOUR = \033[0;96m
COLOUR_END = \033[0m

$(NAME): libft
	@${CC} ${CFLAGS} ${SRC} -L ${LIBFT} -lft -o ${NAME}
#	-L = Opción que indica al compilador dónde encontrar la biblioteca personalizada.
#	-lft = Opción que especifica el nombre de la biblioteca vinculada al programa. El prefijo lib y la extensión .a se omiten por convención.
#	-o = Opción que especifica el nombre del archivo ejecutable que se generará después de compilar.
	@echo "$(COLOUR)Compiled!$(COLOUR_END)"

all: $(NAME)

libft:
	@make -C ${LIBFT}

clean:
	@make clean -C ${LIBFT}
	@$(RM) $(OBJT)

fclean: clean
	@make fclean -C ${LIBFT}
	@$(RM) $(NAME)

re: fclean all clean
#	@echo "$(COLOUR)all rebuilt and *.o cleaned!$(COLOUR_END)"

.PHONY : all clean fclean re
