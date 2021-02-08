/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/08 18:56:20 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int				main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_params	params;
	int			fd;

	mlx = mlx_init();
	mlx_get_screen_size(mlx, &params.def_resol_xy[0], &params.def_resol_xy[1]);
	mlx_win = mlx_new_window(mlx, params.def_resol_xy[0],
							params.def_resol_xy[1], "cube3D");
	img.img = mlx_new_image(mlx, params.def_resol_xy[0],
							params.def_resol_xy[1]);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	fd = open("params.cub", O_RDONLY);
	

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
