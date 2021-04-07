/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapaes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/04/07 09:02:07 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			draw_background(t_set *set)
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
				my_mlx_pixel_put(set, x, y, create_trgb(0, set->scene.c_rgb[0],
				set->scene.c_rgb[1], set->scene.c_rgb[2]));
			if (y > set->scene.rxy[1] / 2)
				my_mlx_pixel_put(set, x, y, create_trgb(0, set->scene.f_rgb[0],
				set->scene.f_rgb[1], set->scene.f_rgb[2]));
			y++;
		}
		y = 0;
		x++;
	}
}

void			fillrect(t_set *set, t_rect rect)
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
