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

void				init_sprite(t_set *set)
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
				s += 1;
			}
			x++;
		}
		x = 0;
		y++;
	}
	// s = 0;
	// while (s < set->scene.sprnum)
	// {
	// 	printf("%d - %d - %d - %d>\n", s,set->sprite[s].x, set->sprite[s].y, set->sprite[s].dist);
	// 	s++;
	// }
}

void				sortspr(t_set *set)
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

float				in_two_pi_range(float rad)
{
	float rad2;

	rad2 = rad;
	while (rad2 >= (2 * PI))
		rad2 -= 2 * PI;
	while (rad2 < 0)
		rad2 += 2 * PI;
	return (rad2);	
}

int					ft_s_color(t_set *set, t_sprite sprite, int x, int y)
{
	int xxpm;
	int yxpm;
	int color;

	xxpm = x / sprite.width * 64;
	yxpm = y / sprite.height * 64;
	color = pixel_color(set, xxpm, yxpm, 4);
	return (color);
}

void				draw_sprite(t_set *set, t_sprite sprite, int xoffset, int yoffset)
{
	(void)set;
	(void)sprite;;
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
		ysprite = 0 + yoffset;
		y = sprite.start_y + yoffset;
		while (y <= sprite.end_y && y < set->ray.pph)
		{
			sprite_color = ft_s_color(set, sprite, xsprite, ysprite);
			if (/*sprite->dist < set->scene.slice*/ sprite_color != 0x00000000)
				my_mlx_pixel_put(set, x, y, sprite_color);
			ysprite++;
			y++;
		}
		xsprite++;
		x++;
	}
	// printf("%d - %d\n", x, y);
	// exit(1);
}

void				draw_sprites(t_set *set)
{
	int		s;
	int xoffset;
	int yoffset;
	float	screen_dist;
	float 	ortho_dist;

	s = 0;
	while (s < set->scene.sprnum)
	{
		screen_dist = (set->ray.ppw / 2) / tan(arcToRad(set->ray.angle60 / 2, set) + (float)(0.000));		
		set->sprite[s].angle = arcToRad(set->pattr.fpa, set) + (float)(0.000);
		// printf("%f\n", set->sprite[s].angle);
		set->sprite[s].angle += atan2(set->sprite[s].y - set->pattr.fpy, set->sprite[s].x - set->pattr.fpx);
		set->sprite[s].angle = in_two_pi_range(set->sprite->angle);
		set->sprite[s].dx =  set->sprite[s].x - set->pattr.fpx; 
		set->sprite[s].dy =  set->sprite[s].y - set->pattr.fpy;
		set->sprite[s].dist = hypot(abs(set->sprite[s].dx), abs(set->sprite[s].dy));
		ortho_dist = set->sprite[s].dist * cos(set->sprite[s].angle);
		set->sprite[s].height = (set->ray.tile_size / ortho_dist) * screen_dist;
		set->sprite[s].width = set->sprite[s].height;
		set->sprite[s].start_y = (set->ray.pph / 2) - (set->sprite[s].height / 2);
		set->sprite[s].end_y = (set->ray.pph / 2) + (set->sprite[s].height / 2) - 1;
		set->sprite[s].left_x = (set->ray.ppw / 2) + tan(set->sprite[s].angle) * screen_dist;
		set->sprite[s].left_x -= set->sprite[s].width / 2;
		set->sprite[s].right_x = set->sprite[s].left_x + set->sprite[s].width - 1;
		printf("%f\n", set->sprite[s].angle);
		exit(-1);
		s++;
	}


	int i;
	int j;
	t_sprite tmp;

	i = 0;
	while (i < set->scene.sprnum - 1)
	{
		j = 0;
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
		// if ()
		while (set->sprite[i].left_x + xoffset < 0)
			xoffset++;
		while (set->sprite[i].start_y + yoffset < 0)
			yoffset++;
		draw_sprite(set, set->sprite[i], xoffset, yoffset);
		i++;	
	}
	
}
