/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/04/07 09:02:10 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void					init_sprite_utils(t_set *set, int *s, int *x, int *y)
{
	set->sprite[*s].x = *x * 64 + 32;
	set->sprite[*s].y = *y * 64 + 32;
	set->sprite[*s].tex = set->scene.spr_t;
	set->sprite[*s].dist = sqrt(pow(abs(set->sprite[*s].x -
	set->pattr.fpx), 2) +
	pow(abs(set->sprite[*s].y - set->pattr.fpy), 2));
	set->sprite[*s].is_visible = 0;
	*s += 1;
}

void					get_spr_val(t_set *set, t_sprite *spr)
{
	float screen_dist;
	float ortho_dist;

	if (spr->is_visible == 0)
		return ;
	screen_dist = fabs((set->ray.ppw / 2) / tan((2 * PI -
	arctorad(set->ray.angle60 / 2, set) + (float)(0.00))));
	spr->angle = fabs(2 * PI - arctorad(set->pattr.fpa, set) + (float)(0.00));
	spr->angle += atan2(spr->y - set->pattr.fpy, spr->x - set->pattr.fpx);
	spr->dist = get_distance(set->pattr.fpx, set->pattr.fpy, spr->x, spr->y);
	ortho_dist = spr->dist * cos(spr->angle);
	spr->height = (set->ray.tile_size / ortho_dist) * screen_dist;
	spr->width = spr->height;
	spr->start_y = (set->ray.pph / 2) - (spr->height / 2);
	spr->end_y = (set->ray.pph / 2) + (spr->height / 2) - 1;
	spr->left_x = (set->ray.ppw / 2) + tan(spr->angle) * screen_dist;
	spr->left_x -= spr->width / 2;
	spr->angle = fabs(spr->angle);
	spr->right_x = spr->left_x + spr->width - 1;
}

void					sprite_utils(t_set *set, int *s, int *i, int *j)
{
	t_sprite	tmp;

	while (*s < set->scene.sprnum)
	{
		get_spr_val(set, &set->sprite[*s]);
		(*s)++;
	}
	*i = 0;
	while (*i < set->scene.sprnum - 1)
	{
		*j = *i;
		while (*j < set->scene.sprnum)
		{
			if (set->sprite[*i].dist < set->sprite[*j].dist)
			{
				tmp = set->sprite[*j];
				set->sprite[*j] = set->sprite[*i];
				set->sprite[*i] = tmp;
				*i = 0;
			}
			(*j)++;
		}
		(*i)++;
	}
}

void					draw_sprites(t_set *set)
{
	int			s;
	int			xyoffset[2];
	int			i;
	int			j;

	s = 0;
	i = 0;
	sprite_utils(set, &s, &i, &j);
	i = 0;
	while (i < set->scene.sprnum)
	{
		xyoffset[0] = 0;
		xyoffset[1] = 0;
		if (set->sprite[i].is_visible == 1)
		{
			while (set->sprite[i].left_x + xyoffset[0] < 0)
				xyoffset[0]++;
			while (set->sprite[i].start_y + xyoffset[1] < 0)
				xyoffset[1]++;
			draw_sprite(set, set->sprite[i], xyoffset[0], xyoffset[1]);
		}
		i++;
	}
}
