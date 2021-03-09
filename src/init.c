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
	set->mlx.win = mlx_new_window(set->mlx.mlx,
	set->scene.rxy[0], set->scene.rxy[1], "cube3D");
	set->mlx.img = mlx_new_image(set->mlx.mlx,
	set->scene.rxy[0], set->scene.rxy[1]);
	set->mlx.addr = mlx_get_data_addr(set->mlx.img,
	&(set->mlx.bpp), &(set->mlx.ll), &(set->mlx.en));
}

static void				conditions(t_set *set, int i)
{
	if (i >= set->ray.angle90 && i < set->ray.angle270)
	{
		set->tabs.fxstept[i] = (float)(set->ray.tile_size / set->tabs.ftant[i]);
		if (set->tabs.fxstept[i] > 0)
			set->tabs.fxstept[i] = -set->tabs.fxstept[i];
	}
	else
	{
		set->tabs.fxstept[i] = (float)(set->ray.tile_size / set->tabs.ftant[i]);
		if (set->tabs.fxstept[i] < 0)
			set->tabs.fxstept[i] = -set->tabs.fxstept[i];
	}
	if (i >= set->ray.angle0 && i < set->ray.angle180)
	{
		set->tabs.fystept[i] = (float)(set->ray.tile_size * set->tabs.ftant[i]);
		if (set->tabs.fystept[i] < 0)
			set->tabs.fystept[i] = -set->tabs.fystept[i];
	}
	else
	{
		set->tabs.fystept[i] = (float)(set->ray.tile_size * set->tabs.ftant[i]);
		if (set->tabs.fystept[i] > 0)
			set->tabs.fystept[i] = -set->tabs.fystept[i];
	}
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
	set->ray.angle30 = (set->ray.angle60/2);
	set->ray.angle15 = (set->ray.angle30/2);
	set->ray.angle90 = (set->ray.angle30*3);
	set->ray.angle180 = (set->ray.angle90*2);
	set->ray.angle270 = (set->ray.angle90*3);
	set->ray.angle360 = (set->ray.angle60*6);
	set->ray.angle0 = 0;
	set->ray.angle5 = (set->ray.angle30/6);
	set->ray.angle10 = (set->ray.angle5*2);
}

void					alloc_tabs(t_set *set)
{
	// malloc(set->ray.angle36)
	set->tabs.fsint = malloc((set->ray.angle360 + 1) * sizeof(float));  
	set->tabs.fisint = malloc((set->ray.angle360 + 1) * sizeof(float)); 
	set->tabs.fcost = malloc((set->ray.angle360 + 1) * sizeof(float));  
	set->tabs.ficost = malloc((set->ray.angle360 + 1) * sizeof(float)); 
	set->tabs.ftant = malloc((set->ray.angle360 + 1) * sizeof(float));  
	set->tabs.fitant = malloc((set->ray.angle360 + 1) * sizeof(float)); 
	set->tabs.ffisht = malloc((set->ray.angle360 + 1) * sizeof(float)); 
	set->tabs.fxstept = malloc((set->ray.angle360 + 1) * sizeof(float));
	set->tabs.fystept = malloc((set->ray.angle360 + 1) * sizeof(float));
}

void					init(t_set *set)
{
	set->mlx.mlx = mlx_init();
	mlx_get_screen_size(set->mlx.mlx, &(set->scene.drxy[0]),
	&(set->scene.drxy[1]));
	if (set->scene.rxy[0] > set->scene.drxy[0])
	{
		set->scene.rxy[0] = set->scene.drxy[0];
		set->ray.ppw = set->scene.drxy[0];
	}
	if (set->scene.rxy[1] > set->scene.drxy[1])
	{
		set->scene.rxy[1] = set->scene.drxy[1];
		set->ray.pph = set->scene.drxy[1];
	}
	init_mlx(set);
	init_ray(set);
	alloc_tabs(set);
	init_tabs(set);
	// set->pattr.fpx = 0;
	// set->pattr.fpy = 0;
	// set->pattr.fpa = ANGLE0;
	// printf("%d\n", set->ray.ppw);
	set->pattr.fpdtopp = 277;
	set->pattr.fph = 32;
	set->pattr.fpseed = 5;
	set->pattr.fppycen = set->scene.rxy[1] / 2;
	// set->tabs.map_h = 8;
	// set->tabs.map_w = 8;
	// set->scene.save = 1;
}
