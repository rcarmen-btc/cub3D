/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/13 21:02:21 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	set_hooks(t_data *data)
{
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_hook(data->win, 2, 1L<<0, key_press_hook, data);
	//mlx_hook(mlx->win, 3, 0, key_release_hook, data);
	//mlx_hook(mlx->win, 4, 0, mouse_press_hook, data->mlx);
	//mlx_hook(mlx->win, 5, 0, mouse_release_hook, data->mlx);
	//mlx_hook(mlx->win, 6, 0, motion_hook, data->mlx);
	//mlx_hook(mlx->win, 12, 0, expose_hook, data->mlx);
	//mlx_hook(mlx->win, 17, 0, exit_hook, data->mlx);
	mlx_hook(data->win, 33, 0, exit_hook, data);
}

//int				render_frame(void *data)
//{
//	t_data *tmp;
//	//int x;
//	//int y;	
//	tmp = data;
//	//x = tmp->x;
//	//y = tmp->y;
//	mlx_clear_window(tmp->mlx, tmp->win);
//	mlx_pixel_put(tmp->mlx, tmp->win, tmp->x, tmp->y, 0x00FFFFFF);
//	//my_mlx_pixel_put(tmp, x, y, 0x00FFFFFF);
//	//int k = x + 20;
//	//int n = y + 20;
//	//while (x < k)
//	//{
//	//	while (y < n)
//	//	{
//	//		my_mlx_pixel_put(tmp, x, y, 0x00FFFFFF);
//	//		y++;
//	//	}
//	//	y = tmp->y;
//	//	x++;
//	//}
//	//mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, 0, 0);
//	return (0);
//}

int				render_frame(void *data)
{
	t_data *tmp;
	tmp = data;

	mlx_clear_window(tmp->mlx, tmp->win);
	print_background(tmp, 0x0FFFF00);
	print_rectangel(tmp, 50, 50, 0x0000FF000);
	mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, 0, 0);
	return (0);
}

void			init(t_data **data)
{
	*data = ft_calloc(sizeof(t_data), 1);
	(*data)->mlx = mlx_init();
	mlx_get_screen_size((*data)->mlx, &((*data)->drxy[0]), &((*data)->drxy[1]));
	(*data)->win = mlx_new_window((*data)->mlx, (*data)->drxy[0], (*data)->drxy[1], "cube3D");
	(*data)->img = mlx_new_image((*data)->mlx, (*data)->drxy[0], (*data)->drxy[1]);
	(*data)->addr = mlx_get_data_addr((*data)->img, &((*data)->bpp), &((*data)->ll), &((*data)->en));
}

int				main(int ac, char **av)
{
	t_data	*data;
	
	if (ac != 2)
		return (-1);
	init(&(data));
	parsing_scene(av, data);
	set_hooks(data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}
