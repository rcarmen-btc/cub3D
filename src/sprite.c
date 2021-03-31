/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/03/31 10:48:00 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void					init_sprite(t_set *set)
{
	int x;
	int y;
	int s;

	s = 0;
	x = 0;
	y = 0;
	set->sprite = ft_calloc(set->scene.sprnum, sizeof(t_sprite));
	while (set->scene.map[y])
	{
		while (set->scene.map[y][x])
		{
			if (set->scene.map[y][x] == '2')
				init_sprite_utils(set, &s, &x, &y);
			x++;
		}
		x = 0;
		y++;
	}
}

float					in_two_pi_range(float rad)
{
	float rad2;

	rad2 = rad;
	while (rad2 >= (2 * PI))
		rad2 -= 2 * PI;
	while (rad2 < 0)
		rad2 += 2 * PI;
	return (rad2);
}

int						ft_s_color(t_set *set, t_sprite sprite, int x, int y)
{
	int xxpm;
	int yxpm;
	int color;

	xxpm = x / sprite.width * 64;
	yxpm = y / sprite.height * 64;
	color = pixel_color(set, xxpm, yxpm, 4);
	return (color);
}

void					draw_sprite(t_set *set, t_sprite sprite,
int xoffset, int yoffset)
{
	int x;
	int y;
	int xsprite;
	int ysprite;
	int sprite_color;

	x = sprite.left_x + xoffset;
	xsprite = 0 + xoffset;
	while (x <= sprite.right_x && x < set->ray.ppw)
	{
		y = sprite.start_y + yoffset;
		ysprite = 0 + yoffset;
		while (y <= sprite.end_y && y < set->ray.pph)
		{
			sprite_color = ft_s_color(set, sprite, xsprite, ysprite);
			(void)sprite_color;
			if (sprite.height > set->scene.dist_be_hit[x] &&
			sprite_color != 0x00000000)
				my_mlx_pixel_put(set, x, y, sprite_color);
			ysprite++;
			y++;
		}
		xsprite++;
		x++;
	}
}

float					get_distance(float x1, float y1, float x2, float y2)
{
	double res;
	double x;
	double y;

	x = (x2 - x1) * (x2 - x1);
	y = (y2 - y1) * (y2 - y1);
	res = sqrt(x + y);
	return ((float)res);
}
