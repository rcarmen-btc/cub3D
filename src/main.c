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

void			set_hooks(t_set *set)
{
	mlx_do_key_autorepeatoff(set->mlx.mlx);
	mlx_hook(set->mlx.win, 2, 1L << 0, key_press_hook, set);
	mlx_hook(set->mlx.win, 3, 1L << 1, key_release_hook, set);
	mlx_hook(set->mlx.win, 17, 0, exit_hook, set);
	mlx_hook(set->mlx.win, 33, 0, exit_hook, set);
}

void			ft_reset_sprites_visibility(t_set *set, int sprite_count)
{
	int i;

	i = 0;
	while (i < sprite_count)
	{
		set->sprite[i].is_visible = 0;
		set->sprite[i].dist = -1;
		i++;
	}
}

int				render_frame(void *set)
{
	t_set		*tmp;

	tmp = set;
	mlx_clear_window(tmp->mlx.mlx, tmp->mlx.win);
	smooth_move(set);
	draw_background(tmp);
	raycasting(set);
	draw_sprites(set);
	mlx_put_image_to_window(tmp->mlx.mlx, tmp->mlx.win, tmp->mlx.img, 0, 0);
	ft_reset_sprites_visibility(set, tmp->scene.sprnum);
	mlx_do_sync(tmp->mlx.mlx);
	return (0);
}

int				main(int ac, char **av)
{
	t_set		set;

	isvalid_arg(ac, av, &set);
	init_before_parse(&set);
	parsing_scene(av, &set);
	init_after_parse(&set);
	get_texture(&set);
	if (set.scene.save == 1)
	{
		if (set.scene.rxy[0] > 11000 || set.scene.rxy[1] > 11000)
			myerror("Error\nToo large scree resolution.\n", 0, &set);
		draw_background(&set);
		raycasting(&set);
		draw_sprites(&set);
		save_bitmap(&set);
	}
	else
	{
		if (NULL == (set.mlx.win = mlx_new_window(set.mlx.mlx,
		set.scene.rxy[0], set.scene.rxy[1], "cube3D")))
			myerror("Error\nIn init.c line: 19\n", 0, &set);
		mlx_loop_hook(set.mlx.mlx, render_frame, &set);
		set_hooks(&set);
		mlx_loop(set.mlx.mlx);
	}
}
