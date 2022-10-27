
FILES = teste mcombeau fractol novo frac2 gamb

all:
	cc fractol.c -lX11 -lXext -lmlx -Imlx -o fractol
	valgrind ./fractol

$(FILES):
	cc $@.c -lX11 -lXext -lmlx -Imlx -o fractol
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