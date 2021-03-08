/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/17 10:52:00 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			my_mlx_pixel_put(t_set *set, int x, int y, int color)
{
	char		*dst;

	dst = set->mlx.addr + (y * set->mlx.ll + x * (set->mlx.bpp / 8));
	*(unsigned int*)dst = color;
}

void	set_hooks(t_set *set)
{
	mlx_do_key_autorepeatoff(set->mlx.mlx);
	mlx_hook(set->mlx.win, 2, 1L<<0, key_press_hook, set);
	//mlx_hook(mlx->win, 3, 0, key_release_hook, data);
	//mlx_hook(mlx->win, 4, 0, mouse_press_hook, data->mlx);
	//mlx_hook(mlx->win, 5, 0, mouse_release_hook, data->mlx);
	//mlx_hook(mlx->win, 6, 0, motion_hook, data->mlx);
	//mlx_hook(mlx->win, 12, 0, expose_hook, data->mlx);
	mlx_hook(set->mlx.win, 17, 0, exit_hook, set);
	mlx_hook(set->mlx.win, 33, 0, exit_hook, set);
}

int				render_frame(void *set)
{
	t_set *tmp;
	tmp = set;

	mlx_clear_window(tmp->mlx.mlx, tmp->mlx.win);
	print_background(tmp, 0x0044C5C);
	print_player(tmp, 64, 64, 0x00CE5A57);
	// for (int i = 0; i < 35; i++)
		// print_fillrect(set, 100 + (5*i), 200 - (5*i), 300 + (10*i));
	mlx_put_image_to_window(tmp->mlx.mlx, tmp->mlx.win, tmp->mlx.img, 0, 0);
	return (0);
}

void			init(t_set *set, char **av)
{
	(void)av;
	set->mlx.mlx = mlx_init();
	mlx_get_screen_size(set->mlx.mlx, &(set->scene.drxy[0]), &(set->scene.drxy[1]));
	set->mlx.win = mlx_new_window(set->mlx.mlx, 
	set->scene.drxy[0], set->scene.drxy[1], "cube3D");
	set->mlx.img = mlx_new_image(set->mlx.mlx,
	set->scene.drxy[0], set->scene.drxy[1]);
	set->mlx.addr = mlx_get_data_addr(set->mlx.img, 
	&(set->mlx.bpp), &(set->mlx.ll), &(set->mlx.en));

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
	int i;
    float radian;

	for (i=0; i<=ANGLE360;i++)
	{
		// get the radian value (the last addition is to avoid division by 0, try removing
		// that and you'll see a hole in the wall when a ray is at 0, 90, 180, or 270 degree)
		radian = arcToRad(i) + (float)(0.0001);
		set->tabs.fsint[i]=(float)sin(radian);
		set->tabs.fisint[i]=(1.0F/(set->tabs.fsint[i]));
		set->tabs.fcost[i]=(float)cos(radian);
		set->tabs.ficost[i]=(1.0F/(set->tabs.fcost[i]));
		set->tabs.ftant[i]=(float)tan(radian);
		set->tabs.fitant[i]=(1.0F/set->tabs.ftant[i]);
		//  you can see that the distance between xi is the same
		//  if we know the angle
		//  _____|_/next xi______________
		//       |
		//  ____/|next xi_________   slope = tan = height / dist between xi's
		//     / |
		//  __/__|_________  dist between xi = height/tan where height=tile size
		// old xi|
		//                  distance between xi = x_step[view_angle];
		//
		//
		// facine left
		// facing left
		if (i>=ANGLE90 && i<ANGLE270)
		{
			set->tabs.fxstept[i] = (float)(TILE_SIZE/set->tabs.ftant[i]);
			if (set->tabs.fxstept[i]>0)
				set->tabs.fxstept[i]=-set->tabs.fxstept[i];
		}
		// facing right
		else
		{
			set->tabs.fxstept[i] = (float)(TILE_SIZE/set->tabs.ftant[i]);
			if (set->tabs.fxstept[i]<0)
				set->tabs.fxstept[i]=-set->tabs.fxstept[i];
		}
		// FACING DOWN
		if (i >= ANGLE0 && i < ANGLE180)
		{
			set->tabs.fystept[i] = (float)(TILE_SIZE*set->tabs.ftant[i]);
			if (set->tabs.fystept[i]<0)
				set->tabs.fystept[i]=-set->tabs.fystept[i];
		}
		// FACING UP
		else
		{
			set->tabs.fystept[i] = (float)(TILE_SIZE*set->tabs.ftant[i]);
			if (set->tabs.fystept[i]>0)
				set->tabs.fystept[i]=-set->tabs.fystept[i];
		}
	}

	for (i=-ANGLE30; i<=ANGLE30; i++)
	{
		radian = arcToRad(i);
		// we don't have negative angle, so make it start at 0
		// this will give range 0 to 320
		set->tabs.ffisht[i+ANGLE30] = (float)(1.0F/cos(radian));
	}
}

int				main(int ac, char **av)
{
	t_set		set;

	isvalid_arg(ac, av, &set);
	init(&set, av);
	parsing_scene(av, &set);
	set_hooks(&set);
	mlx_loop_hook(set.mlx.mlx, render_frame, &set);
	mlx_loop(set.mlx.mlx);
}
