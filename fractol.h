/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s < rleite-s@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:49:22 by rleite-s          #+#    #+#             */
/*   Updated: 2022/10/29 07:11:26 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>

#define MAX_ITERATIONS 80
#define WIDTH 800
#define HEIGHT 800

typedef struct  s_fractol
{
	long double  min_r;
	long double  max_r;
	long double  min_i;
	long double  max_i;
}   t_fractol;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			color;
	int			tes;
	t_fractol	*frac;
}			t_mlx;

int		close_window(t_mlx *mlx);
int		muda_cor(int tecla, t_mlx *mlx);
int		teste_mouse(int keymask, int x, int y, t_mlx *mlx);
void	mandelbrot(t_mlx *mlx, int x, int y, long double cr, long double ci);
void	fractal_init(t_fractol * frac);
void	move(int key, t_mlx *mlx);
void	zoom_in(t_mlx *mlx);
void	zoom_out(t_mlx *mlx);
void	draw_fractal(t_mlx *f);
int		pinta_linha(t_mlx *mlx);
void	pixel_put(t_mlx *data, int x, int y, int color);



#endif