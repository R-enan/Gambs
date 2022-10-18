#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdio.h>

#define MAX_ITERATIONS 100 // Maximum number of iterations
#define WIDTH 800	// Width of the window (in pixels)
#define HEIGHT 800	// Height of the window (in pixels)

// Structure for the fractol variables
typedef struct  s_fractol
{
	long double  min_r;	// Minimum value of real axis
	long double  max_r;	// Maximum value of real axis
	long double  min_i;	// Minimum value of imaginary axis
	long double  max_i;	// Maximum value of imaginary axis
}   t_fractol;

// Struct of mlx
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		color;
	int		tes;
	t_fractol	*frac;
}			t_mlx;

// Function of Aurelien Brabant
void	pixel_put(t_mlx *data, int x, int y, int color);

// Funcion of Mcombeau
void	mandelbrot(t_mlx *mlx, int x, int y, long double cr, long double ci)
{
	int	n;	// Number of iterations
	long double	zr;	// Real part of Z
	long double	zi;	// Imaginary part of Z
	long double	tmp;	// Temporary variable
	// Variable to determine if a number is in the set or not:
	int	is_in_set;

	zr = 0;
	zi = 0;
	n = -1;
	is_in_set = 1;
	while (++n < MAX_ITERATIONS + mlx->tes)
	{
		// As long as we're not at the maximum number of iterations,
		// we iterate
		if ((zr * zr + zi * zi) > 4.0)
		{
			// If the absolute value of Z exceeds 2
			// (zr * zr + zi * zi) > 4.0 == sqrt(zr * zr + zi * zi) > 2
			is_in_set = 0;
			// We flag that this number tends toward infinity,
			// and is therefore not part of the set
			// and we stop iterating
			break ;
		}
		// Calculate the Mandelbrot formula for the next iteration
		tmp = 2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
	}

	/**************************************************************
	*
	*	Aqui só pintamos com cores diferenciadas.
	*
	**************************************************************/
	// If the number is part of the Mandelbrot set,
	// set the pixel to black, otherwise to white
	if (is_in_set == 1)
		//mlx_pixel_put(mlx->mlx, mlx->win, x, y, mlx->color);
		pixel_put(mlx, x, y, mlx->color); // Aqui é o Mandelbrot
	/*else if (n > MAX_ITERATIONS / 2)
		//mlx_pixel_put(mlx->mlx, mlx->win, x, y,  0xFFFFFF / mlx->color);
		pixel_put(mlx, x, y, (0xFFFFFF - 0x000000) * n + 0x000000);*/
	else
		pixel_put(mlx, x, y, mlx->color * 0xFFFFFF * n); // Aqui é as bordas;
		//pixel_put(mlx, x, y, mlx->color * 0xFFFFFF * n);
		//(endValue - startValue) * stepNumber / lastStepNumber + startValue
}

void	draw_fractal(t_mlx *f)
{
	// x and y coordinates of the pixel:
	int	x; // column
	int	y; // line
	// to map the x and y coordinates of the pixel to a
	// complex number:
	long double	pr; // real part of the complex number of the pixel
	long double	pi; // imaginary part of the complex number of the pixel

	// Loop over each line and column of the window
	// to check each pixels
	y = -1;
	while (++y < HEIGHT) // line loop
	{
		x = -1;
		while (++x < WIDTH) // column loop
		{
			// Find pixel[x, y]'s corresponding complex number
			pr = f->frac->min_r + (long double)x * (f->frac->max_r - f->frac->min_r) / WIDTH;
			pi = f->frac->min_i + (long double)y * (f->frac->max_i - f->frac->min_i) / HEIGHT;
			// Evaluate it and set this pixel's color
			mandelbrot(f, x, y, pr, pi);
		}
	}
}

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	zoom_in(t_mlx *mlx)
{
	mlx->frac->min_r += (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
	mlx->frac->max_r -= (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
	mlx->frac->min_i += (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
	mlx->frac->max_i = mlx->frac->min_i + (mlx->frac->max_r - mlx->frac->min_r) * HEIGHT / WIDTH;
}

void	zoom_out(t_mlx *mlx)
{
	mlx->frac->min_r -= (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
	mlx->frac->max_r += (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
	mlx->frac->min_i -= (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
	mlx->frac->max_i = mlx->frac->min_i + (mlx->frac->max_r - mlx->frac->min_r) * HEIGHT / WIDTH;
}

// Aqui é uma função que captura a leitura do teclado.
int	muda_cor(int tecla, t_mlx *mlx)
{
	// Destrói janela
	if (tecla == XK_Escape)
	{
		//mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		//mlx_destroy_display(mlx->mlx);
		mlx->win = NULL;
	}
	// Muda cores
	if (tecla == XK_a)
		mlx->color += 0x0f00f110;
	if (tecla == XK_d)
		mlx->color -= 0x0f00f110;
	
	// Zoom out
	if (tecla == XK_x)
	{
		zoom_out(mlx);
		mlx->tes -= 0.5; // Para melhoramento de imagens
	}
	// Zoom in
	if (tecla == XK_z)
	{
		zoom_in(mlx);
		mlx->tes += 0.5; // Para melhoramento de imagens
	}

	// Movimento "a câmera"
	if (tecla == XK_Up)
	{
		mlx->frac->min_i -= (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
		mlx->frac->max_i -= (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
	}
	if (tecla == XK_Down)
	{
		mlx->frac->min_i += (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
		mlx->frac->max_i += (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
	}
	if (tecla == XK_Left)
	{
		mlx->frac->min_r -= (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
		mlx->frac->max_r -= (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
		mlx->frac->max_i = mlx->frac->min_i + (mlx->frac->max_r - mlx->frac->min_r) * HEIGHT / WIDTH;
	}
	if (tecla == XK_Right)
	{
		mlx->frac->min_r += (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
		mlx->frac->max_r += (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
		mlx->frac->max_i = mlx->frac->min_i + (mlx->frac->max_r - mlx->frac->min_r) * HEIGHT / WIDTH;
	}

	// Reseta tudo
	if (tecla == XK_r)
	{
		mlx->frac->min_r = - 2;
		mlx->frac->max_r = 1;
		mlx->frac->min_i = -1.5;
		mlx->frac->max_i = mlx->frac->min_i + (mlx->frac->max_r - mlx->frac->min_r) * HEIGHT / WIDTH;
	}
	return (0);
}

// Loop Hook (pra evento de pintar janela)
int	pinta_linha(t_mlx *mlx)
{
	/* for (int i = 0; i < 300; i++)
		pixel_put(mlx, i, i, mlx->color);
	if (mlx->tes == 1)
	{
		for (int i = 230; i < 530; i++)
			pixel_put(mlx, i/2 + 10, i + 10, mlx->color);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, -50, 0);
	} */
	draw_fractal(mlx);
	if (mlx->win)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	teste_mouse(int keymask, int y, t_mlx *mlx)
{
	printf("\nEvento: %d\n", keymask);
	if (keymask == 4)
	{

	}
	else if (keymask == 5)
	{

	}
	printf("Coordenadas: (%d, %d)\n", y, y);
	return (0);
}

int		mlx_mouse_move(void *mlx, void *win, int x, int y)
{
	printf("(%d, %d)\t", x, y);
	return (0);
}

int	main(void)
{
	t_mlx mlx;
	t_fractol	frac;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Janela Qualquer <3");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_len, &mlx.endian);

{
	// Cor inicial
	mlx.color = 0x0000FF;
	mlx.tes = 0;

	// Coordenadas do plano inicial
	frac.min_r = -2.0;
	// Value of complex numbers on right edge of window:
	frac.max_r = 1.0;
	// Value of complex numbers on top edge of window:
	frac.min_i = -1.5;
	// Value of complex numbers on bottom edge of window:
	frac.max_i = frac.min_i + (frac.max_r - frac.min_r) * HEIGHT / WIDTH;
	mlx.frac = &frac;
}

	// Inserir evento de janela
	mlx_loop_hook(mlx.mlx, &pinta_linha, &mlx);

	// Inserir evento de captura de teclado
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &muda_cor, &mlx);

	// Inserir eventos de mouse
	mlx_mouse_hook(mlx.win, teste_mouse, &mlx);



	// Mostra a janela
	mlx_loop(mlx.mlx);

	// frees e destroys padrão
	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_display(mlx.mlx);
	free(mlx.mlx);
	return (0);
}

/***
Threads: http://cocic.cm.utfpr.edu.br/progconcorrente/doku.php?id=c_pthreads
***/