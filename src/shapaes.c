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
			if (y < set->scene.drxy[1] / 2)
				my_mlx_pixel_put(set, x, y, color);
			if (y > set->scene.drxy[1] / 2)
				my_mlx_pixel_put(set, x, y, 0x00FF32F0);
			y++;
		}
		y = 0;
		x++;
	}
}

void print_fillrect(t_set *set, int x, int y, int h)
{
	int w;
	int i;

	w = 1;
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