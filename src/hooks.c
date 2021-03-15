/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/17 11:08:55 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "linux_kcode.h"

int						key_press_hook(int keycode, t_set *set)
{
	if (keycode == MLX_KEY_LEFT)
		set->kfl.left = 1;
	else if (keycode == MLX_KEY_RIGHT)
		set->kfl.right = 1;
	if (keycode == MLX_KEY_D)
		set->kfl.d = 1;
	if (keycode == MLX_KEY_A)
		set->kfl.a = 1;
	if (keycode == MLX_KEY_W)
		set->kfl.w = 1;
	if (keycode == MLX_KEY_S)
		set->kfl.s = 1;
	if (keycode == MLX_KEY_SHIFT_L)
		set->pattr.fpseed += 5;
	if (keycode == MLX_KEY_ESCAPE)
		exit_hook(set);
	return (0);
}

int						key_release_hook(int keycode, t_set *set)
{
	if (keycode == MLX_KEY_W)
		set->kfl.w = 0;
	if (keycode == MLX_KEY_A)
		set->kfl.a = 0;
	if (keycode == MLX_KEY_S)
		set->kfl.s = 0;
	if (keycode == MLX_KEY_D)
		set->kfl.d = 0;
	if (keycode == MLX_KEY_LEFT)
		set->kfl.left = 0;
	if (keycode == MLX_KEY_RIGHT)
		set->kfl.right = 0;
	if (keycode == MLX_KEY_SHIFT_L)
		set->pattr.fpseed -= 5;
	return (0);
}

static void				smooth_move_utils(t_set *set)
{
	if (set->kfl.a == 1 &&
	set->scene.map[((set->pattr.fpy - (int)(set->pattr.playerxd *
	set->pattr.fpseed * 2)) / 64)][(((set->pattr.fpx +
	(int)(set->pattr.playeryd * set->pattr.fpseed * 2)) / 64))] != '1')
	{
		set->pattr.fpx += (int)(set->pattr.playeryd * set->pattr.fpseed);
		set->pattr.fpy -= (int)(set->pattr.playerxd * set->pattr.fpseed);
	}
	if (set->kfl.s == 1 &&
	set->scene.map[(((set->pattr.fpy - (int)(set->pattr.playeryd *
	set->pattr.fpseed * 2)) / 64))][((set->pattr.fpx -
	(int)(set->pattr.playerxd * set->pattr.fpseed * 2)) / 64)] != '1')
	{
		set->pattr.fpx -= (int)(set->pattr.playerxd * set->pattr.fpseed);
		set->pattr.fpy -= (int)(set->pattr.playeryd * set->pattr.fpseed);
	}
	if (set->kfl.d == 1 &&
	set->scene.map[((set->pattr.fpy + (int)(set->pattr.playerxd *
	set->pattr.fpseed * 2)) / 64)][(((set->pattr.fpx -
	(int)(set->pattr.playeryd * set->pattr.fpseed * 2)) / 64))] != '1')
	{
		set->pattr.fpx -= (int)(set->pattr.playeryd * set->pattr.fpseed);
		set->pattr.fpy += (int)(set->pattr.playerxd * set->pattr.fpseed);
	}
}

void					smooth_move(t_set *set)
{
	if (set->kfl.left == 1)
	{
		if ((set->pattr.fpa -= set->ray.angle10 / 2) < set->ray.angle0)
			set->pattr.fpa += set->ray.angle360;
	}
	if (set->kfl.right == 1)
	{
		if ((set->pattr.fpa += set->ray.angle10 / 2) >= set->ray.angle360)
			set->pattr.fpa -= set->ray.angle360;
	}
	set->pattr.playerxd = set->tabs.fcost[set->pattr.fpa];
	set->pattr.playeryd = set->tabs.fsint[set->pattr.fpa];
	if (set->kfl.w == 1 &&
	set->scene.map[(((set->pattr.fpy + (int)(set->pattr.playeryd *
	set->pattr.fpseed * 2)) / 64))][((set->pattr.fpx +
	(int)(set->pattr.playerxd * set->pattr.fpseed * 2)) / 64)] != '1')
	{
		set->pattr.fpx += (int)(set->pattr.playerxd * set->pattr.fpseed);
		set->pattr.fpy += (int)(set->pattr.playeryd * set->pattr.fpseed);
	}
	smooth_move_utils(set);
}

int						exit_hook(void *set)
{
	free_mlx(set);
	free_scene(set);
	free_tabs(set);
	exit(0);
}
