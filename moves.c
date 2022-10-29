/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s < rleite-s@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:54:33 by rleite-s          #+#    #+#             */
/*   Updated: 2022/10/28 03:29:00 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move(int key, t_mlx *mlx)
{
	if (key == XK_Up)
	{
		mlx->frac->min_i -= (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
		mlx->frac->max_i -= (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
	}
	if (key == XK_Down)
	{
		mlx->frac->min_i += (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
		mlx->frac->max_i += (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
	}
	if (key == XK_Left)
	{
		mlx->frac->min_r -= (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
		mlx->frac->max_r -= (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
	}
	if (key == XK_Right)
	{
		mlx->frac->min_r += (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
		mlx->frac->max_r += (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
	}
}

void	zoom_in(t_mlx *mlx)
{
	if (mlx->tes < 800)
	{
		mlx->frac->min_r += (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
		mlx->frac->max_r -= (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
		mlx->frac->min_i += (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
		mlx->frac->max_i = mlx->frac->min_i + (mlx->frac->max_r - mlx->frac->min_r) * HEIGHT / WIDTH;
		mlx->tes += 5;
	}
}

void	zoom_out(t_mlx *mlx)
{
	if (mlx->tes > -175)
	{	
		mlx->frac->min_r -= (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
		mlx->frac->max_r += (mlx->frac->max_i - mlx->frac->min_i) * 0.115;
		mlx->frac->min_i -= (mlx->frac->max_r - mlx->frac->min_r) * 0.115;
		mlx->frac->max_i = mlx->frac->min_i + (mlx->frac->max_r - mlx->frac->min_r) * HEIGHT / WIDTH;
		mlx->tes -= 5;
	}
}
