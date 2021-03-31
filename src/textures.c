/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/03/31 10:48:11 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			get_texture(t_set *set)
{
	int w;
	int h;

	w = 64;
	h = 64;
	if (NULL == (set->texture[0].img = mlx_xpm_file_to_image(set->mlx.mlx,
	set->scene.ea_t, &w, &h)))
		myerror("Error\nInvalid EA texture path or file isn't readable.\n",
		0, set);
	set->texture[0].addr = mlx_get_data_addr(set->texture[0].img,
	&(set->texture[0].bpp), &(set->texture[0].ll), &(set->texture[0].en));
	if (w != 64 || h != 64)
		myerror("Error\nInvalid EA texture resolution >/< then 64X64.\n",
		0, set);
	if (NULL == (set->texture[1].img = mlx_xpm_file_to_image(set->mlx.mlx,
	set->scene.no_t, &w, &h)))
		myerror("Error\nInvalid NO texture path or file isn't readable.\n",
		0, set);
	set->texture[1].addr = mlx_get_data_addr(set->texture[1].img,
	&(set->texture[1].bpp), &(set->texture[1].ll), &(set->texture[1].en));
	if (w != 64 || h != 64)
		myerror("Error\nInvalid NO texture resolution >/< then 64X64.\n",
		0, set);
	get_texture_utils(set);
}

void			filltexrect(t_set *set, t_rect rect)
{
	int i;

	i = 0;
	set->line.x0 = rect.x;
	set->line.y0 = rect.y;
	set->line.x1 = rect.x;
	set->line.y1 = rect.y + rect.h;
	while (i < rect.w)
	{
		draw_line_tex(set, rect);
		i++;
		set->line.x0++;
		set->line.x1++;
	}
}

static void		xbiggery(t_set *set, t_rect rect)
{
	set->line.y = set->line.y0;
	set->line.x = set->line.x0;
	set->line.tmp = set->line.deltay > 0 ? 1 : -1;
	set->line.direction = set->line.deltay != 0 ? set->line.tmp : 0;
	while (set->line.deltax > 0 ? set->line.x <= set->line.x1 : set->line.x
	>= set->line.x1)
	{
		my_mlx_pixel_put(set, set->line.x, set->line.y,
		pixel_color(set, rect.tx, rect.ty, rect.tnum));
		set->line.accrection += set->line.abs_deltay;
		if (set->line.accrection >= set->line.abs_deltax)
		{
			set->line.accrection -= set->line.abs_deltax;
			set->line.y += set->line.direction;
		}
		set->line.deltax > 0 ? set->line.x++ : set->line.x--;
		rect.ty += rect.ty_step;
	}
}

static void		ybiggerx(t_set *set, t_rect rect)
{
	set->line.y = set->line.y0;
	set->line.x = set->line.x0;
	set->line.tmp = set->line.deltax > 0 ? 1 : -1;
	set->line.direction = set->line.deltax != 0 ? set->line.tmp : 0;
	while (set->line.deltay > 0 ? set->line.y <= set->line.y1 : set->line.y
	>= set->line.y1)
	{
		my_mlx_pixel_put(set, set->line.x, set->line.y,
		pixel_color(set, rect.tx, rect.ty, rect.tnum));
		set->line.accrection += set->line.abs_deltax;
		if (set->line.accrection >= set->line.abs_deltay)
		{
			set->line.accrection -= set->line.abs_deltay;
			set->line.x += set->line.direction;
		}
		set->line.deltay > 0 ? set->line.y++ : set->line.y--;
		rect.ty += rect.ty_step;
	}
}

void			draw_line_tex(t_set *set, t_rect rect)
{
	set->line.deltax = set->line.x1 - set->line.x0;
	set->line.deltay = set->line.y1 - set->line.y0;
	set->line.abs_deltax = abs(set->line.deltax);
	set->line.abs_deltay = abs(set->line.deltay);
	set->line.accrection = 0;
	if (set->line.abs_deltax >= set->line.abs_deltay)
		xbiggery(set, rect);
	else
		ybiggerx(set, rect);
}
