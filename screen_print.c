/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s < rleite-s@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:24:22 by rleite-s          #+#    #+#             */
/*   Updated: 2022/10/29 07:14:04 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_fractal(t_mlx *f)
{
	int			x;
	int			y;
	long double	pr;
	long double	pi;

	y = -1;
	while (++y < HEIGHT) 
	{
		x = -1;
		while (++x < WIDTH / 2) 
		{
			pr = f->frac->min_r + x * (f->frac->max_r - f->frac->min_r) / WIDTH;
			pi = f->frac->min_i + y * (f->frac->max_i - f->frac->min_i) / \
			HEIGHT;
			mandelbrot(f, x, y, pr, pi);
			pr = f->frac->min_r + (x + WIDTH / 2)* (f->frac->max_r - f->frac->min_r) / WIDTH;
			pi = f->frac->min_i + y * (f->frac->max_i - f->frac->min_i) / \
			HEIGHT;
			mandelbrot(f, x + WIDTH / 2, y, pr, pi);
		}
	}
}

int	pinta_linha(t_mlx *mlx)
{
	draw_fractal(mlx);
	if (mlx->win)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
