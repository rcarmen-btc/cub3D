/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapaes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/16 01:37:16 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			print_background(t_data *data, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < data->drxy[0])
	{
		while (y < data->drxy[1])
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
}

void			print_player(t_data *data, int sizex, int sizey, int color)
{
	int x;
	int y;
	int k;
	int n;

	x = data->px;
	y = data->py;
	k = x + sizex;
	n = y + sizey;
	while (x < k)
	{
		while (y < n)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		y = data->py;
		x++;
	}
	print_line(data, data->px + data->pdx * 5, data->py + data->pdy * 5);
}

void			print_square(t_data *data, int x, int y, int color)
{
	int k;
	int n;
	int start_y;

	start_y = y;
	k = x + 20;
	n = y + 20;
	while (x < k)
	{
		while (y < n)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		y = start_y;
		x++;
	}
}

void			print_map(t_data *data)
{
	int x;
	int y;
	int sqr_s;
	int color;

	x = 0;
	y = 0;
	sqr_s = 20;
	color = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0')
				color = 0x0044C5C;
			else
				color = 0x00E1B16A;
			print_square(data, x * sqr_s, y * sqr_s, color);
			x++;
		}
		x = 0;
		y++;
	}
}
