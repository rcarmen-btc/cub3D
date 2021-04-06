/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:30:55 by rcarmen           #+#    #+#             */
/*   Updated: 2021/04/06 09:44:07 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

float						arctorad(float arcangle, t_set *set)
{
	return ((float)(arcangle * PI) / (float)set->ray.angle180);
}

void						check_tex_rect(t_rect *rect, t_set *set)
{
	if (rect->x > set->scene.rxy[0])
		rect->x = set->scene.rxy[0];
	if (rect->y > set->scene.rxy[1])
		rect->y = set->scene.rxy[1];
	if (rect->h > set->scene.rxy[1])
		rect->h = abs(rect->y - set->scene.rxy[1]);
}

void						print_ray(t_set *set, t_rect *rect)
{
	rect->h = set->ray.projwhei - 1;
	set->scene.dist_be_hit[set->ray.castcolumn] = rect->h;
	rect->h = abs(rect->h);
	rect->w = 1;
	rect->x = abs(set->ray.castcolumn);
	rect->y = abs(set->ray.topOfWall);
	if (rect->tnum == 1 || rect->tnum == 0)
		rect->tx = abs(rect->xoffset);
	else
		rect->tx = abs(rect->xoffset);
	rect->ty = fabs(rect->ty_off * rect->ty_step);
	check_tex_rect(rect, set);
	if (set->pattr.fpx >= 0 && set->pattr.fpy >= 0)
		filltexrect(set, *rect);
	set->ray.castarc += 1;
	if (set->ray.castarc >= set->ray.angle360)
		set->ray.castarc -= set->ray.angle360;
}

void						handle_ray(t_set *set, t_rect *rect)
{
	if (set->ray.ditohorgrbehit < set->ray.ditovergrbehit)
	{
		set->ray.dist = set->ray.ditohorgrbehit;
		rect->xoffset = (int)set->ray.xinter % set->ray.tile_size;
		rect->side = 0;
	}
	else
	{
		set->ray.dist = set->ray.ditovergrbehit;
		rect->xoffset = (int)set->ray.yinter % set->ray.tile_size;
		rect->side = 1;
	}
	if (rect->side == 0)
	{
		if (set->ray.ditonehorg > 0)
			rect->tnum = 1;
		else
			rect->tnum = 3;
	}
	else
	{
		(set->ray.ditoneverg > 0) ? rect->tnum = 2 : 0;
		(set->ray.ditoneverg <= 0) ? rect->tnum = 0 : 0;
	}
}

void						raycasting(t_set *set)
{
	t_rect	rect;

	set->ray.topOfWall = 0;
	set->ray.bottomOfWall = 0;
	set->ray.castarc = set->pattr.fpa;
	set->ray.castarc -= set->ray.angle30;
	set->ray.castcolumn = 0;
	if (set->ray.castarc < 0)
		set->ray.castarc += set->ray.angle360;
	while (set->ray.castcolumn < set->ray.ppw)
	{
		vertical_wall(set);
		horizontal_wall(set);
		handle_ray(set, &rect);
		raycasting_set(set, &rect);
		print_ray(set, &rect);
		set->ray.castcolumn += 1;
	}
}
