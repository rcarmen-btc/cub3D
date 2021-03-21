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

static void				init_mlx(t_set *set)
{
	if (NULL == (set->mlx.win = mlx_new_window(set->mlx.mlx,
	set->scene.rxy[0], set->scene.rxy[1], "cube3D")))
		myerror("Error\nIn init.c line: 19\n", 4, set);
	if (NULL == (set->mlx.img = mlx_new_image(set->mlx.mlx,
	set->scene.rxy[0], set->scene.rxy[1])))
		myerror("Error\nIN init.c line: 22\n", 3, set);
	set->mlx.addr = mlx_get_data_addr(set->mlx.img,
	&(set->mlx.bpp), &(set->mlx.ll), &(set->mlx.en));
}

static void				conditions(t_set *set, int i)
{
	if (i >= set->ray.angle90 && i < set->ray.angle270)
	{
		set->tabs.fxstept[i] = (float)(set->ray.tile_size /
		set->tabs.ftant[i]);
		if (set->tabs.fxstept[i] > 0)
			set->tabs.fxstept[i] = -set->tabs.fxstept[i];
	}
	else
	{
		set->tabs.fxstept[i] = (float)(set->ray.tile_size /
		set->tabs.ftant[i]);
		if (set->tabs.fxstept[i] < 0)
			set->tabs.fxstept[i] = -set->tabs.fxstept[i];
	}
	additional_condition(set, i);
}

static void				init_tabs(t_set *set)
{
	int					i;
	float				radian;

	i = 0;
	while (i <= set->ray.angle360)
	{
		radian = arcToRad(i, set) + (float)(0.0001);
		set->tabs.fsint[i] = (float)sin(radian);
		set->tabs.fisint[i] = (1.0F / (set->tabs.fsint[i]));
		set->tabs.fcost[i] = (float)cos(radian);
		set->tabs.ficost[i] = (1.0F / (set->tabs.fcost[i]));
		set->tabs.ftant[i] = (float)tan(radian);
		set->tabs.fitant[i] = (1.0F / set->tabs.ftant[i]);
		conditions(set, i);
		i++;
	}
	i = -set->ray.angle30;
	while (i <= set->ray.angle30)
	{
		radian = arcToRad(i, set);
		set->tabs.ffisht[i + set->ray.angle30] = (float)(1.0F / cos(radian));
		i++;
	}
}

void					init_ray(t_set *set)
{
	set->ray.tile_size = 64;
	set->ray.wall_height = 64;
	set->ray.angle60 = set->ray.ppw;
	set->ray.angle30 = (set->ray.angle60 / 2);
	set->ray.angle15 = (set->ray.angle30 / 2);
	set->ray.angle90 = (set->ray.angle30 * 3);
	set->ray.angle180 = (set->ray.angle90 * 2);
	set->ray.angle270 = (set->ray.angle90 * 3);
	set->ray.angle360 = (set->ray.angle60 * 6);
	set->ray.angle0 = 0;
	set->ray.angle5 = (set->ray.angle30 / 6);
	set->ray.angle10 = (set->ray.angle5 * 2);
}

void					init(t_set *set)
{		
	if (NULL == (set->mlx.mlx = mlx_init()))
		myerror("Error\nIn init.c line: 90 in mlx_init function.\n", 3, set);
	mlx_get_screen_size(set->mlx.mlx, &(set->scene.drxy[0]),
	&(set->scene.drxy[1]));
	if (set->scene.rxy[0] > set->scene.drxy[0])
		set->scene.rxy[0] = set->scene.drxy[0];
	set->ray.ppw = set->scene.rxy[0];
	if (set->scene.rxy[1] > set->scene.drxy[1])
		set->scene.rxy[1] = set->scene.drxy[1];
	set->ray.pph = set->scene.rxy[1];
	init_mlx(set);
	init_ray(set);
	find_player(set);
	alloc_tabs(set);
	init_tabs(set);
	set->kfl.w = 0;
	set->ray.forhook = 0;
	set->pattr.fpdtopp = set->ray.ppw / 2 / set->tabs.ftant[set->ray.angle30];
	set->pattr.fph = 32;
	set->pattr.fpseed = 8;
	float del = (float)(set->scene.rxy[0]) / (float)(set->scene.rxy[1]);
	int w = set->scene.rxy[0];
	int h = set->scene.rxy[1];
	if (del > 7.01f)
		myerror("Error\nToo small height\n", 0, set);
	if (del < 0.494f)
		myerror("Error\nToo small width\n", 0, set);
	if (w < 300 && h < 300)
		set->pattr.fpseed = 2;
	else if (w < 500 && h < 500)
		set->pattr.fpseed = 4;
	else if (w < 700 && h < 700)
		set->pattr.fpseed = 6;
	else
		set->pattr.fpseed = 8;
	set->pattr.fppycen = set->ray.pph / 2;
}
