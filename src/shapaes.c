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
	while (x < set->scene.rxy[0])
	{
		while (y < set->scene.rxy[1])
		{
			if (y < set->scene.rxy[1] / 2)
				my_mlx_pixel_put(set, x, y, color);
			if (y > set->scene.rxy[1] / 2)
				my_mlx_pixel_put(set, x, y, 0x00FF32F0);
			y++;
		}
		y = 0;
		x++;
	}
}

void fillrect(t_set *set, t_rect rect)
{
	int i;

	i = 0;
	set->line.x0 = rect.x;
	set->line.y0 = rect.y;
	set->line.x1 = rect.x;
	set->line.y1 = rect.y + rect.h;
	while (i < rect.w)
	{
		draw_line(set, rect.color);
		i++;
		set->line.x0++;
		set->line.x1++;
	}
}