/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/17 12:59:34 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void init_sprite(t_set *set)
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
			{
				set->sprite[s].x = x * 64 + 32;
				set->sprite[s].y = y * 64 + 32;
				set->sprite[s].tex = set->scene.spr_t;
				set->sprite[s].dist = sqrt(pow(abs(set->sprite[s].x - set->pattr.fpx), 2) + pow(abs(set->sprite[s].y - set->pattr.fpy), 2));
				set->sprite[s].is_visible = 0;
				s += 1;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void sortspr(t_set *set)
{
	(void)set;
}

// void				draw_one_sprite(t_set *set, int s)
// {

// 	float spr_dir = atan2(set->sprite[s].y - set->pattr.fpy, set->sprite[s].x - set->pattr.fpx);
// 	while (spr_dir - arcToRad(set->pattr.fpa, set) > PI)
// 	{
// 		spr_dir -= 2 * PI;
// 	}
// 	while (spr_dir - arcToRad(set->pattr.fpa, set) < -PI)
// 	{
// 		spr_dir += 2 * PI;
// 	}
// 	set->sprite[s].dx = set->pattr.fpx - set->sprite[s].x;
// 	set->sprite[s].dy = set->pattr.fpy - set->sprite[s].y;
// 	set->sprite[s].dist = hypot(set->sprite[s].dx, set->sprite[s].dy);
// 	int sprite_size = set->ray.pph / set->sprite[s].dist;`
// 	int hoffset = (spr_dir - arcToRad(set->pattr.fpa, set)) * (set->ray.ppw / 2) / arcToRad(set->ray.angle60, set) + set->ray.ppw / 2 - sprite_size / 2;
// 	int voffset = set->ray.pph / 2 - sprite_size / 2;
// 	for (int i=0; i<sprite_size; i++)
// 	{
//         if (hoffset+(int)(i)<0 || hoffset+i>=set->ray.ppw/2)
// 			continue;
//         for (int j=0; j<sprite_size; j++)
// 		{
//             if (voffset+(int)(j)<0 || voffset+j>=set->ray.pph)
// 				continue;
// 			my_mlx_pixel_put(set, set->ray.ppw / 2 + hoffset + i, voffset + j, 0x00000000);
//             // fb.set_pixel(fb.w/2 + h_offset+i, v_offset+j, pack_color(0,0,0));
//         }
//     }
// }

float in_two_pi_range(float rad)
{
	float rad2;

	rad2 = rad;
	while (rad2 >= (2 * PI))
		rad2 -= 2 * PI;
	while (rad2 < 0)
		rad2 += 2 * PI;
	return (rad2);
}

int ft_s_color(t_set *set, t_sprite sprite, int x, int y)
{
	int xxpm;
	int yxpm;
	int color;

	xxpm = x / sprite.width * 64;
	yxpm = y / sprite.height * 64;
	color = pixel_color(set, xxpm, yxpm, 4);
	return (color);
}

void draw_sprite(t_set *set, t_sprite sprite, int xoffset, int yoffset)
{
	(void)set;
	(void)sprite;
	(void)xoffset;
	(void)yoffset;
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
			if (sprite.height > set->scene.dist_be_hit[x] && sprite_color != 0x00000000)
				my_mlx_pixel_put(set, x, y, sprite_color);
			ysprite++;
			y++;
		}
		xsprite++;
		x++;
	}
	// printf("%f - %f\n", sprite.right_x, sprite.start_y);
	// exit(1);
}

float get_distance(float x1, float y1, float x2, float y2)
{
	double res;
	double x;
	double y;

	x = (x2 - x1) * (x2 - x1);
	y = (y2 - y1) * (y2 - y1);
	res = sqrt(x + y);
	return ((float)res);
}
	
void			get_spr_val(t_set *set, t_sprite *spr)
{
	float screen_dist;
	float ortho_dist;

	if (spr->is_visible == 0)
		return ;
	screen_dist = fabs((set->ray.ppw / 2) / tan((2 * PI - arcToRad(set->ray.angle60 / 2, set) + (float)(0.00))));
	spr->angle = fabs(2 * PI - arcToRad(set->pattr.fpa, set) + (float)(0.00));
	// printf("1.%f\n", spr->angle);
	spr->angle += atan2(spr->y - set->pattr.fpy, spr->x - set->pattr.fpx);
	// printf("2.%f\n", spr->angle);
	// spr->angle = in_two_pi_range(set->sprite->angle);
	// printf("3.%f\n", spr->angle);
	// spr->dx = (spr->x - set->pattr.fpx);
	// spr->dy = (spr->y - set->pattr.fpy);
	// spr->dist = hypot(abs(spr->dx), abs(spr->dy));
	spr->dist = get_distance(set->pattr.fpx, set->pattr.fpy, spr->x, spr->y);
	// printf("%d - %d - %d - %d\n", spr->x, spr->y, set->pattr.fpx, set->pattr.fpx);
	// printf("%f\n", screen_dist);
	ortho_dist = spr->dist * cos(spr->angle);
	// printf("%f\n", ortho_dist);
	spr->height = (set->ray.tile_size / ortho_dist) * screen_dist;
	spr->width = spr->height;
	spr->start_y = (set->ray.pph / 2) - (spr->height / 2);
	spr->end_y = (set->ray.pph / 2) + (spr->height / 2) - 1;
	spr->left_x = (set->ray.ppw / 2) + tan(spr->angle) * screen_dist;
	spr->left_x -= spr->width / 2;
	// spr->left_x = fabs(spr->left_x);
	spr->angle = fabs(spr->angle);
	spr->right_x = spr->left_x + spr->width - 1;
	// printf("%f - %f\n", spr->left_x, spr->angle);
	// printf("%f - %f - %d\n", spr->angle, spr->dist, spr->is_visible);
	// exit(-1);
}


void draw_sprites(t_set *set)
{
	int s;
	int xoffset;
	int yoffset;

	s = 0;
	// set->sprite[0].is_visible = 0;
	while (s < set->scene.sprnum)
	{
		get_spr_val(set, &set->sprite[s]);
		s++;
	}

	int i;
	int j;
	t_sprite tmp;

	i = 0;
	while (i < set->scene.sprnum - 1)
	{
		j = i;
		while (j < set->scene.sprnum)
		{
			if (set->sprite[i].dist < set->sprite[j].dist)
			{
				tmp = set->sprite[j];
				set->sprite[j] = set->sprite[i];
				set->sprite[i] = tmp;
				i = 0;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < set->scene.sprnum)
	{
		xoffset = 0;
		yoffset = 0;
		if (set->sprite[i].is_visible == 1)
		{
			while (set->sprite[i].left_x + xoffset < 0)
				xoffset++;
			while (set->sprite[i].start_y + yoffset < 0)
				yoffset++;
			draw_sprite(set, set->sprite[i], xoffset, yoffset);
		}
		i++;
	}
}
