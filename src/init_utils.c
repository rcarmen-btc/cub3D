/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/04/03 22:42:42 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void					init_scene(t_set *set)
{
	int i;

	i = 0;
	while (i < 3)
	{
		set->scene.c_rgb[i] = -1;
		set->scene.f_rgb[i] = -1;
		i++;
	}
	set->scene.ea_t = NULL;
	set->scene.no_t = NULL;
	set->scene.we_t = NULL;
	set->scene.so_t = NULL;
	set->scene.spr_t = NULL;
	set->scene.sprnum = 0;
	set->scene.map = NULL;
	set->scene.rxy[0] = 0;
	set->scene.rxy[1] = 0;
}

void					init_after_parse(t_set *set)
{
	if (set->scene.rxy[0] == 0)
		myerror("Error\nWindow width is zero.\n", 0, set);
	if (set->scene.rxy[1] == 0)
		myerror("Error\nWindow height is zero.\n", 0, set);
	init_mlx(set);
	init_ray(set);
	find_player(set);
	alloc_tabs(set);
	init_tabs(set);
	init_pattr(set);
	check_trgb(set);
	isvalid_map(set);
}

void					init_before_parse(t_set *set)
{
	if (NULL == (set->mlx.mlx = mlx_init()))
		myerror("Error\nIn init.c line: 90 in mlx_init function.\n", 0, set);
	mlx_get_screen_size(set->mlx.mlx, &(set->scene.drxy[0]),
	&(set->scene.drxy[1]));
	set->ray.forhook = 0;
	init_scene(set);
}
