/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/11 12:58:17 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int				main(int ac, char **av)
{
	//void		*mlx;
	//void		*mlx_win;
	//t_data		img;
	t_params	*params;
	int			fd;

	if (ac != 2)
		return (-1);
	params = ft_calloc(sizeof(t_params), 1);
	fd = open(*(av + 1), O_RDONLY);
	parsing_scene(fd, params);
	//mlx = mlx_init();
	//mlx_get_screen_size(mlx, &params.def_resol_xy[0], &params.def_resol_xy[1]);
	//mlx_win = mlx_new_window(mlx, params.def_resol_xy[0],
								//params.def_resol_xy[1], "cube3D");
	//img.img = mlx_new_image(mlx,params.def_resol_xy[0],
	//							params.def_resol_xy[1]);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	//								&img.endian);


	ft_printf("%s\n", params->sprite_t);
	//ft_printf("%s\n", (char *)params->map[5]);

	
	//mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	//mlx_loop(mlx);

	free(params->ea_t);
	free(params->we_t);
	free(params->so_t);
	free(params->no_t);
	free(params->sprite_t);
	int i = 0;
	while (i < 15)
	{
		free(params->map[i]);
		i++;
	}
	free(params->map);
	free(params);
}
