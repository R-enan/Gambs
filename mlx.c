/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s < rleite-s@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:22:18 by rleite-s          #+#    #+#             */
/*   Updated: 2022/10/29 07:41:59 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fractal_init(t_fractol *frac)
{
	frac->min_r = -2.0;
	frac->max_r = 1.0;
	frac->min_i = -1.5;
	frac->max_i = frac->min_i + (frac->max_r - frac->min_r) * HEIGHT / WIDTH;
}

long double ft_atof(char *str)
{
	long double	num;
	int			signal;
	
	signal = (*str == '-');
	str += (*str == '+' || *str == '-');
	while (*str && *str != '.' && *str >= '0' && *str <= '9')
	{
		num = (num * 10) + *str - '0';
		str++;
	}
	str += (*str == '.');
	while (*str && *str != '.' && *str >= '0' && *str <= '9')
	{
		
		str++;
	}
	return (num);
}

void	message ()
{
	
}
 
int		check_arguments(char **argv)
{
	while (*argv)
	{
		
	}
	return (1);
}

int	main(int argc, char **argv)
{
	check_arguments(argv);
	t_mlx		mlx;
	t_fractol	frac;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Janela Qualquer <3");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_len, &mlx.endian);
	mlx.color = 0x0000FF;
	mlx.tes = 0;
	fractal_init(&frac);
	mlx.frac = &frac;
	mlx_loop_hook(mlx.mlx, &pinta_linha, &mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &muda_cor, &mlx);
	mlx_mouse_hook(mlx.win, teste_mouse, &mlx);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_display(mlx.mlx);
	free(mlx.mlx);
	return (0);
}
