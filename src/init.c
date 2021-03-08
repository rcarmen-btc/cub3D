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
	set->mlx.mlx = mlx_init();
	mlx_get_screen_size(set->mlx.mlx, &(set->scene.drxy[0]),
	&(set->scene.drxy[1]));
	set->mlx.win = mlx_new_window(set->mlx.mlx,
	set->scene.drxy[0], set->scene.drxy[1], "cube3D");
	set->mlx.img = mlx_new_image(set->mlx.mlx,
	set->scene.drxy[0], set->scene.drxy[1]);
	set->mlx.addr = mlx_get_data_addr(set->mlx.img,
	&(set->mlx.bpp), &(set->mlx.ll), &(set->mlx.en));
}

static void				conditions(t_set *set, int i)
{
	if (i >= ANGLE90 && i < ANGLE270)
	{
		set->tabs.fxstept[i] = (float)(TILE_SIZE / set->tabs.ftant[i]);
		if (set->tabs.fxstept[i] > 0)
			set->tabs.fxstept[i] = -set->tabs.fxstept[i];
	}
	else
	{
		set->tabs.fxstept[i] = (float)(TILE_SIZE / set->tabs.ftant[i]);
		if (set->tabs.fxstept[i] < 0)
			set->tabs.fxstept[i] = -set->tabs.fxstept[i];
	}
	if (i >= ANGLE0 && i < ANGLE180)
	{
		set->tabs.fystept[i] = (float)(TILE_SIZE * set->tabs.ftant[i]);
		if (set->tabs.fystept[i] < 0)
			set->tabs.fystept[i] = -set->tabs.fystept[i];
	}
	else
	{
		set->tabs.fystept[i] = (float)(TILE_SIZE * set->tabs.ftant[i]);
		if (set->tabs.fystept[i] > 0)
			set->tabs.fystept[i] = -set->tabs.fystept[i];
	}
}

static void				init_tabs(t_set *set)
{
	int					i;
	float				radian;

	i = 0;
	while (i <= ANGLE360)
	{
		radian = arcToRad(i) + (float)(0.0001);
		set->tabs.fsint[i] = (float)sin(radian);
		set->tabs.fisint[i] = (1.0F / (set->tabs.fsint[i]));
		set->tabs.fcost[i] = (float)cos(radian);
		set->tabs.ficost[i] = (1.0F / (set->tabs.fcost[i]));
		set->tabs.ftant[i] = (float)tan(radian);
		set->tabs.fitant[i] = (1.0F / set->tabs.ftant[i]);
		conditions(set, i);
		i++;
	}
	i = -ANGLE30;
	while (i <= ANGLE30)
	{
		radian = arcToRad(i);
		set->tabs.ffisht[i + ANGLE30] = (float)(1.0F / cos(radian));
		i++;
	}
}

void					init(t_set *set)
{
	init_mlx(set);
	init_tabs(set);
	set->pattr.fpx = 0;
	set->pattr.fpy = 0;
	set->pattr.fpa = ANGLE0;
	set->pattr.fpdtopp = 277;
	set->pattr.fph = 32;
	set->pattr.fpseed = 16;
	set->pattr.fppycen = PROJECTIONPLANEHEIGHT / 2;
	set->tabs.map_h = 8;
	set->tabs.map_w = 8;
	set->scene.save = 1;
}
