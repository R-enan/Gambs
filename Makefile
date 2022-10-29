NAME	= fractol

FILES		= mlx.c events.c mandelbrot.c moves.c screen_print.c
OBJ			= $(FILES:.c=.o)

CFLAGS		= -Wall -Werror -Wextra
MLXFLAGS	= -lX11 -lXext -lmlx 
MLXINCLUDE	= -Imlx

RM		= rm -f

%.o: %.c
	cc $(CFLAGS) -c $< $(MLXINCLUDE) -o $@

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $^ $(MLXINCLUDE) $(MLXFLAGS) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re



#
# SE LEMBRE DE APAGAR o que vier embaixo
# SE LEMBRE DE APAGAR o que vier embaixo
# SE LEMBRE DE APAGAR o que vier embaixo
#

AQUI = teste mcombeau novo frac2 gamb

$(AQUI):
	cc $(CFLAGS) $@.c -Imlx -lX11 -lXext -lmlx  -o fractol
#	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./fractol
	./fractol

rm:
	rm -f fractol vgcore*

git:
	@git add .
	@git commit -m "$(m)"
	@git push

file:
	@touch $(f).c && code-server $(f).c
	
.PHONY: git