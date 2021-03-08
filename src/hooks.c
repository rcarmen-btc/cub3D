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

int			key_press_hook(int keycode, t_set *set)
{
	if (keycode == MLX_KEY_LEFT)
	{
		if ((set->pattr.fpa-=ANGLE10)<ANGLE0)
			set->pattr.fpa+=ANGLE360;
	}
	else if (keycode == MLX_KEY_RIGHT)
	{
		if ((set->pattr.fpa+=ANGLE10)>=ANGLE360)
			set->pattr.fpa-=ANGLE360;
	}
	float playerXDir=set->tabs.fcost[set->pattr.fpa];
	float playerYDir=set->tabs.fsint[set->pattr.fpa];
	if (keycode == MLX_KEY_D && set->pattr.fpx + 5 <= set->scene.drxy[0])
	{
		set->pattr.fpx-= (int)(playerYDir*set->pattr.fpseed);
        set->pattr.fpy+= (int)(playerXDir*set->pattr.fpseed);
	}
	else if (keycode == MLX_KEY_A && set->pattr.fpx - 5 >= 0)
	{
		set->pattr.fpx+= (int)(playerYDir*set->pattr.fpseed);
        set->pattr.fpy-= (int)(playerXDir*set->pattr.fpseed);
	}
	else if (keycode == MLX_KEY_W && set->pattr.fpy - 5 >= 0)
	{
		set->pattr.fpx+=(int)(playerXDir*set->pattr.fpseed);
        set->pattr.fpy+=(int)(playerYDir*set->pattr.fpseed);
	}
	else if (keycode == MLX_KEY_S && set->pattr.fpy + 5 <= set->scene.drxy[1])
	{
		set->pattr.fpx-=(int)(playerXDir*set->pattr.fpseed);
        set->pattr.fpy-=(int)(playerYDir*set->pattr.fpseed);
	}
	else if (keycode == MLX_KEY_ESCAPE)
		exit_hook(set);
	return (0);
}

int			exit_hook(void *set)
{
	free_mlx(set);
	free_scene(set);
	exit(0);
}
