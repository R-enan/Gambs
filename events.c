/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s < rleite-s@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:27:12 by rleite-s          #+#    #+#             */
/*   Updated: 2022/10/29 05:29:11 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Usar enum pra pegar o evento e chamar a função correspondente
int	close_window(t_mlx *mlx)
{	
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx->win = NULL;
	exit(0);
	return (0);
}

int	muda_cor(int tecla, t_mlx *mlx)
{
	if (tecla == XK_Escape)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
	else if (tecla == XK_a)
		mlx->color += 0x0f00f110;
	else if (tecla == XK_d)
		mlx->color -= 0x0f00f110;
	else if (tecla == XK_x)
		zoom_out(mlx);
	else if (tecla == XK_z)
		zoom_in(mlx);
	else if (tecla == XK_Up || tecla == XK_Down || tecla == XK_Left
		|| tecla == XK_Right)
		move(tecla, mlx);
	else if (tecla == XK_r)
	{
		fractal_init(mlx->frac);
		mlx->tes = 0;
	}
	return (0);
}

int	teste_mouse(int keymask, int x, int y, t_mlx *mlx)
{
	if (keymask == 4)
		zoom_in(mlx);
	else if (keymask == 5)
		zoom_out(mlx);
	// Bônus com relação ao cursor pode ser feito com base no valor de x e y... mas como???
	x = y;
	y = x;
	//printf("Coordenadas: (%d, %d)\n", x, y);
	return (0);
}
