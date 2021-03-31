/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:30:55 by rcarmen           #+#    #+#             */
/*   Updated: 2021/03/31 16:34:55 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void						raycasting_set(t_set *set, t_rect *rect)
{
	set->ray.dist /= set->tabs.ffisht[set->ray.castcolumn];
	set->ray.projwhei = (int)(set->ray.wall_height *
	(float)set->pattr.fpdtopp / set->ray.dist);
	if (set->ray.ppw / 2 == set->ray.castcolumn)
		set->ray.forhook = set->ray.projwhei;
	set->ray.bottomOfWall = set->pattr.fppycen +
	(int)(set->ray.projwhei * 0.5F);
	set->ray.topOfWall = set->pattr.fppycen -
	(int)(set->ray.projwhei * 0.5F);
	if (set->ray.bottomOfWall >= set->ray.pph)
		set->ray.bottomOfWall = set->ray.pph - 1;
	if (set->ray.topOfWall < 0 || set->ray.topOfWall >= set->ray.ppw)
		set->ray.topOfWall = 0;
	rect->ty_step = 64.0 / (float)set->ray.projwhei;
	rect->ty_off = 0;
	if (set->ray.projwhei > set->ray.pph)
	{
		rect->ty_off = (set->ray.projwhei - set->ray.pph) / 2.0;
		set->ray.projwhei = set->ray.pph;
	}
}

void						ver_up_down(t_set *set)
{
	if (set->ray.castarc > set->ray.angle0 &&
	set->ray.castarc < set->ray.angle180)
	{
		set->ray.horizontalgrid = (set->pattr.fpy / set->ray.tile_size)
		* set->ray.tile_size + set->ray.tile_size;
		set->ray.ditonehorg = set->ray.tile_size;
		set->ray.xtemp = set->tabs.fitant[set->ray.castarc] *
		(set->ray.horizontalgrid - set->pattr.fpy);
		set->ray.xinter = set->ray.xtemp + set->pattr.fpx;
	}
	else
	{
		set->ray.horizontalgrid = (set->pattr.fpy / set->ray.tile_size) *
		set->ray.tile_size;
		set->ray.ditonehorg = -set->ray.tile_size;
		set->ray.xtemp = set->tabs.fitant[set->ray.castarc] *
		(set->ray.horizontalgrid - set->pattr.fpy);
		set->ray.xinter = set->ray.xtemp + set->pattr.fpx;
		set->ray.horizontalgrid--;
	}
}

void						hor_up_down(t_set *set)
{
	if (set->ray.castarc < set->ray.angle90 ||
	set->ray.castarc > set->ray.angle270)
	{
		set->ray.verticalgrid = set->ray.tile_size + (set->pattr.fpx /
		set->ray.tile_size) * set->ray.tile_size;
		set->ray.ditoneverg = set->ray.tile_size;
		set->ray.ytemp = set->tabs.ftant[set->ray.castarc] *
		(set->ray.verticalgrid - set->pattr.fpx);
		set->ray.yinter = set->ray.ytemp + set->pattr.fpy;
	}
	else
	{
		set->ray.verticalgrid = (set->pattr.fpx / set->ray.tile_size)
		* set->ray.tile_size;
		set->ray.ditoneverg = -set->ray.tile_size;
		set->ray.ytemp = set->tabs.ftant[set->ray.castarc] *
		(set->ray.verticalgrid - set->pattr.fpx);
		set->ray.yinter = set->ray.ytemp + set->pattr.fpy;
		set->ray.verticalgrid--;
	}
}

int							ver_ray_loop(t_set *set)
{
	int i;

	set->ray.x_grid_index = (int)(set->ray.xinter / set->ray.tile_size);
	set->ray.y_grid_index = (set->ray.horizontalgrid / set->ray.tile_size);
	if ((set->ray.x_grid_index >= set->tabs.map_w) ||
		(set->ray.y_grid_index >= set->tabs.map_h) ||
		set->ray.x_grid_index < 0 || set->ray.y_grid_index < 0)
	{
		set->ray.ditohorgrbehit = __FLT_MAX__;
		return (1);
	}
	if ((set->scene.map[set->ray.y_grid_index]
	[set->ray.x_grid_index]) == '2')
	{
		i = 0;
		while (i < set->scene.sprnum)
		{
			if (set->sprite[i].x / 64 == set->ray.x_grid_index &&
			set->sprite[i].y / 64 == set->ray.y_grid_index)
				set->sprite[i].is_visible = 1;
			i++;
		}
	}
	return (0);
}

void						vertical_wall(t_set *set)
{
	ver_up_down(set);
	if (set->ray.castarc == set->ray.angle0 ||
	set->ray.castarc == set->ray.angle180)
		set->ray.ditohorgrbehit = __FLT_MAX__;
	else
	{
		set->ray.ditonexinter = set->tabs.fxstept[set->ray.castarc];
		while (1)
		{
			if (ver_ray_loop(set) == 1)
				break ;
			if ((set->scene.map[set->ray.y_grid_index]
			[set->ray.x_grid_index]) == '1')
			{
				set->ray.ditohorgrbehit = (set->ray.xinter - set->pattr.fpx) *
				set->tabs.ficost[set->ray.castarc];
				break ;
			}
			else
			{
				set->ray.xinter += set->ray.ditonexinter;
				set->ray.horizontalgrid += set->ray.ditonehorg;
			}
		}
	}
}
