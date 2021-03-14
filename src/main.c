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
	mlx_hook(set->mlx.win, 3, 1L<<1, key_release_hook, set);
	//mlx_hook(mlx->win, 4, 0, mouse_press_hook, data->mlx);
	//mlx_hook(mlx->win, 5, 0, mouse_release_hook, data->mlx);
	//mlx_hook(mlx->win, 6, 0, motion_hook, data->mlx);
	//mlx_hook(mlx->win, 12, 0, expose_hook, data->mlx);
	mlx_hook(set->mlx.win, 17, 0, exit_hook, set);
	mlx_hook(set->mlx.win, 33, 0, exit_hook, set);
}

int				render_frame(void *set)
{
	t_set 		*tmp;
	tmp = set;

	mlx_clear_window(tmp->mlx.mlx, tmp->mlx.win);
	print_background(tmp, 0x0044C5C);
	while (tmp->kfl.w == 1)
	{
		set->pattr.fpx+=(int)(playerXDir*set->pattr.fpseed);
        set->pattr.fpy+=(int)(playerYDir*set->pattr.fpseed);
	}
	
	raycasting(set);
	mlx_put_image_to_window(tmp->mlx.mlx, tmp->mlx.win, tmp->mlx.img, 0, 0);

	return (0);
}

int				main(int ac, char **av)
{
	t_set		set;

	isvalid_arg(ac, av, &set);
	parsing_scene(av, &set);
	init(&set);
	get_texture(&set);	
	mlx_loop_hook(set.mlx.mlx, render_frame, &set);
	set_hooks(&set);
	mlx_loop(set.mlx.mlx);
}
