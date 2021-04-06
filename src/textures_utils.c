/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/04/05 11:33:44 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		util(t_set *set)
{
	int w;
	int h;

	w = 64;
	h = 64;
	if (NULL == (set->texture[4].img = mlx_xpm_file_to_image(set->mlx.mlx,
	set->scene.spr_t, &w, &h)))
		myerror("Error\nInvalid sprite texture path or file isn't readable.\n",
		0, set);
	set->texture[4].addr = mlx_get_data_addr(set->texture[4].img,
	&(set->texture[4].bpp), &(set->texture[4].ll), &(set->texture[4].en));
	if (w != 64 || h != 64)
		myerror("Error\nInvalid S resolution >/< then 64X64.\n", 0, set);
	init_sprite(set);
}

void			get_texture_utils(t_set *set)
{
	int w;
	int h;

	w = 64;
	h = 64;
	if (NULL == (set->texture[2].img = mlx_xpm_file_to_image(set->mlx.mlx,
	set->scene.we_t, &w, &h)))
		myerror("Error\nInvalid WA texture path or file isn't readable.\n",
		0, set);
	set->texture[2].addr = mlx_get_data_addr(set->texture[2].img,
	&(set->texture[2].bpp), &(set->texture[2].ll), &(set->texture[2].en));
	if (w != 64 || h != 64)
		myerror("Error\nInvalid WA texture resolution >/< then 64X64.\n",
		0, set);
	if (NULL == (set->texture[3].img = mlx_xpm_file_to_image(set->mlx.mlx,
	set->scene.so_t, &w, &h)))
		myerror("Error\nInvalid SO texture path or file isn't readable.\n",
		0, set);
	set->texture[3].addr = mlx_get_data_addr(set->texture[3].img,
	&(set->texture[3].bpp), &(set->texture[3].ll), &(set->texture[3].en));
	if (w != 64 || h != 64)
		myerror("Error\nInvalid SO texture resolution >/< then 64X64.\n",
		0, set);
	util(set);
}
