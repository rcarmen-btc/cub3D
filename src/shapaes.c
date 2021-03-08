/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapaes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/17 11:45:25 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			print_background(t_set *set, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < set->scene.drxy[0])
	{
		while (y < set->scene.drxy[1])
		{
			my_mlx_pixel_put(set, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
}

void			print_player(t_set *set, int sizex, int sizey, int color)
{
	// int x;
	// int y;
	// int k;
	// int n;
	(void)sizex;
	(void)sizey;
	(void)color;
	// x = data->px;
	// y = data->py;
	// k = x + sizex;
	// n = y + sizey;
	// while (x < k)
	// {
	// 	while (y < n)
	// 	{
	// 		my_mlx_pixel_put(data, x, y, color);
	// 		y++;
	// 	}
	// 	y = data->py;
	// 	x++;
	// }
	// set->pattr.fPlayerX+=32;
	// set->pattr.fPlayerY+=32;
	// print_line(data, data->px + data->pdx * 5, data->py + data->pdy * 5);
	print_ray(set);
	// set->pattr.fPlayerX-=32;
	// set->pattr.fPlayerY-=32;
}

void			print_square(t_set *set, int x, int y, int color)
{
	int k;
	int n;
	int start_y;

	start_y = y;
	k = x + 64;
	n = y + 64;
	while (x < k)
	{
		while (y < n)
		{
			my_mlx_pixel_put(set, x, y, color);
			y++;
		}
		y = start_y;
		x++;
	}
}

void			print_map(t_set *set)
{
	int x;
	int y;
	int sqr_s;
	int color;

	x = 0;
	y = 0;
	sqr_s = 64;
	color = 0;
	while (set->scene.map[y])
	{
		while (set->scene.map[y][x])
		{
			if (set->scene.map[y][x] == '0')
				color = 0x0044C5C;
			else if (set->scene.map[y][x] == '1')
				color = 0x00E1B16A;
			print_square(set, x * sqr_s, y * sqr_s, color);
			x++;
		}
		x = 0;
		y++;
	}
}

void print_fillrect(t_set *set, int x, int y, int h)
{
	int w;
	int i;

	w = 5;
	i = 0;
	set->line.x0 = x;
	set->line.y0 = y;
	set->line.x1 = x;
	set->line.y1 = y + h;
	while (i < w)
	{
		print_line(set);
		i++;
		set->line.x0++;
		set->line.x1++;
	}
}