/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/03/31 16:41:51 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void						alloc_tabs(t_set *set)
{
	set->scene.dist_be_hit = ft_calloc(set->scene.rxy[0], sizeof(int));
	set->tabs.fsint = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fisint = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fcost = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.ficost = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.ftant = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fitant = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.ffisht = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fxstept = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fystept = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	if (NULL == set->scene.dist_be_hit || NULL == set->tabs.fsint
	|| NULL == set->tabs.fisint || NULL == set->tabs.fcost
	|| NULL == set->tabs.ficost || NULL == set->tabs.ftant
	|| NULL == set->tabs.fitant || NULL == set->tabs.ffisht
	|| NULL == set->tabs.fxstept || NULL == set->tabs.fystept)
		myerror("Error\nIn utils.c line 17-16 with ft_calloc.", 0, set);
}

void						additional_condition(t_set *set, int i)
{
	if (i >= set->ray.angle0 && i < set->ray.angle180)
	{
		set->tabs.fystept[i] = (float)(set->ray.tile_size *
		set->tabs.ftant[i]);
		if (set->tabs.fystept[i] < 0)
			set->tabs.fystept[i] = -set->tabs.fystept[i];
	}
	else
	{
		set->tabs.fystept[i] = (float)(set->ray.tile_size *
		set->tabs.ftant[i]);
		if (set->tabs.fystept[i] > 0)
			set->tabs.fystept[i] = -set->tabs.fystept[i];
	}
}

int							where_player(t_set *set, char c, int x, int y)
{
	int			pcount;

	pcount = 0;
	if (ft_isdigit(c))
	{
		(c == '2') ? set->scene.sprnum += 1 : 0;
		(c != '2' && c != '0' && c != '1') ? myerror(INV, 0, set) : 0;
	}
	if (ft_isalpha(c))
	{
		if (c == 'N')
			set->pattr.fpa = set->ray.angle270;
		else if (c == 'W')
			set->pattr.fpa = set->ray.angle180;
		else if (c == 'E')
			set->pattr.fpa = set->ray.angle0;
		else if (c == 'S')
			set->pattr.fpa = set->ray.angle90;
		else
			myerror(INV, 0, set);
		set->pattr.fpx = x * 64 + 32;
		set->pattr.fpy = y * 64 + 32;
		pcount += 1;
	}
	return (pcount);
}

int							get_wrd_cnt(char const *s, char c)
{
	int		wrd_cnt;
	int		i;
	int		is;

	i = 0;
	is = 1;
	wrd_cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i++] != c)
		{
			if (is == 1)
				wrd_cnt++;
			is = 0;
		}
		else
			is = 1;
	}
	return (wrd_cnt);
}

int							hor_ray_loop(t_set *set)
{
	int i;

	set->ray.x_grid_index = (set->ray.verticalgrid / set->ray.tile_size);
	set->ray.y_grid_index = (int)(set->ray.yinter / set->ray.tile_size);
	if ((set->ray.x_grid_index >= set->tabs.map_w) ||
		(set->ray.y_grid_index >= set->tabs.map_h) ||
		set->ray.x_grid_index < 0 || set->ray.y_grid_index < 0)
	{
		set->ray.ditovergrbehit = __FLT_MAX__;
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
