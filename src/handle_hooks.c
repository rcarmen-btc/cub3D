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
		set->pattr.fpx+=(int)(playerXDir*set->pattr.fpseed);
	else if (keycode == MLX_KEY_A && set->pattr.fpx - 5 >= 0)
        set->pattr.fpy+=(int)(playerYDir*set->pattr.fpseed);
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
	return (0);
}

int			exit_hook(void *set)
{
	int		i;
	(void)set;
	mlx_clear_window(((t_set *)set)->mlx.mlx, ((t_set *)set)->mlx.win);
	mlx_destroy_image(((t_set *)set)->mlx.mlx, ((t_set *)set)->mlx.img);
	mlx_destroy_window(((t_set *)set)->mlx.mlx, ((t_set *)set)->mlx.win);
	mlx_destroy_display(((t_set *)set)->mlx.mlx);
	free(((t_set *)set)->mlx.mlx);
	free(((t_set *)set)->scene.ea_t);
	free(((t_set *)set)->scene.we_t);
	free(((t_set *)set)->scene.so_t);
	free(((t_set *)set)->scene.no_t);
	free(((t_set *)set)->scene.spr_t);
	i = 0;
	while (i < 8)
	{
		free(((t_set *)set)->scene.map[i]);
		i++;
	}
	free(((t_set *)set)->scene.map);
	// free((t_set *)set);
	exit(0);
}
