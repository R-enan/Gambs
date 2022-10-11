#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>

#define MAX_ITERATIONS 80 // Maximum number of iterations
#define WIDTH 600	// Width of the window (in pixels)
#define HEIGHT 600	// Height of the window (in pixels)

// Structure for the fractol variables
typedef struct  s_fractol
{
	double  min_r;	// Minimum value of real axis
	double  max_r;	// Maximum value of real axis
	double  min_i;	// Minimum value of imaginary axis
	double  max_i;	// Maximum value of imaginary axis
}   t_fractol;

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
	t_fractol	frac;
}			t_mlx;

void	pixel_put(t_mlx *data, int x, int y, int color);

void	mandelbrot(t_mlx *mlx, int x, int y, double cr, double ci)
{
	int	n;	// Number of iterations
	double	zr;	// Real part of Z
	double	zi;	// Imaginary part of Z
	double	tmp;	// Temporary variable
	// Variable to determine if a number is in the set or not:
	int	is_in_set; 

	zr = 0;
	zi = 0;
	n = -1;
	is_in_set = 1;
	while (++n < MAX_ITERATIONS)
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
	// If the number is part of the Mandelbrot set,
	// set the pixel to black, otherwise to white
	if (is_in_set == 1)
		//mlx_pixel_put(mlx->mlx, mlx->win, x, y, mlx->color);
		pixel_put(mlx, x, y, mlx->color);
	else if (n >= MAX_ITERATIONS / 2)
		//mlx_pixel_put(mlx->mlx, mlx->win, x, y,  0xFFFFFF / mlx->color);
		pixel_put(mlx, x, y, mlx->color + 0x00FFFF * n);
	else
		pixel_put(mlx, x, y, mlx->color * 0x00FFFF * n);
}

void	draw_fractal(t_mlx *f)
{
	// x and y coordinates of the pixel:
	int	x; // column
	int	y; // line
	// to map the x and y coordinates of the pixel to a
	// complex number:
	double	pr; // real part of the complex number of the pixel
	double	pi; // imaginary part of the complex number of the pixel

	// Loop over each line and column of the window
	// to check each pixels
	y = -1;
	while (++y < HEIGHT) // line loop
	{
		x = -1;
		while (++x < WIDTH) // column loop
		{
			// Find pixel[x, y]'s corresponding complex number
			pr = f->frac.min_r + (double)x * (f->frac.max_r - f->frac.min_r) / WIDTH;
			pi = f->frac.min_i + (double)y * (f->frac.max_i - f->frac.min_i) / HEIGHT;
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

int	muda_cor(int tecla, t_mlx *mlx)
{
	if (tecla == XK_Escape)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
	if (tecla == XK_a)
		mlx->color += 0x0f00f110;
	if (tecla == XK_d)
		mlx->color -= 0x0f00f110;
	if (tecla == XK_Down)
	{
		mlx->frac.min_r -= 0.115;
		mlx->frac.max_r += 0.115;
		mlx->frac.min_i -= 0.115;
		mlx->frac.max_i = mlx->frac.min_i + (mlx->frac.max_r - mlx->frac.min_r) * HEIGHT / WIDTH;
	}
	if (tecla == XK_Up)
	{
		mlx->frac.min_r += 0.115;
		mlx->frac.max_r -= 0.115;
		mlx->frac.min_i += 0.115;
		mlx->frac.max_i = mlx->frac.min_i + (mlx->frac.max_r - mlx->frac.min_r) * HEIGHT / WIDTH;
	}
	if (tecla == XK_Left)
	{
		mlx->frac.min_r -= (mlx->frac.max_r - mlx->frac.min_r) * 0.115;
		mlx->frac.max_r -= (mlx->frac.max_r - mlx->frac.min_r) * 0.115;
	}
	if (tecla == XK_Right)
	{
		mlx->frac.min_r += (mlx->frac.max_r - mlx->frac.min_r) * 0.115;
		mlx->frac.max_r += (mlx->frac.max_r - mlx->frac.min_r) * 0.115;
	}
	return (0);
}

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
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_mlx mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 800, 800, "Janela Qualquer <3");
	mlx.img = mlx_new_image(mlx.mlx, 600, 600);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_len, &mlx.endian);

{
	mlx.color = 0x0000FF;
	mlx.tes = 0;

	mlx.frac.min_r = -2.0;
	// Value of complex numbers on right edge of window:
	mlx.frac.max_r = 1.0;
	// Value of complex numbers on top edge of window:
	mlx.frac.min_i = -1.5;
	// Value of complex numbers on bottom edge of window:
	mlx.frac.max_i = mlx.frac.min_i + (mlx.frac.max_r - mlx.frac.min_r) * HEIGHT / WIDTH;
}
	
	mlx_loop_hook(mlx.mlx, &pinta_linha, &mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &muda_cor, &mlx);

	mlx_loop(mlx.mlx);

	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_display(mlx.mlx);
	free(mlx.mlx);
	return (0);
}
