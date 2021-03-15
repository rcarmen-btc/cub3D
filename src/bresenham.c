/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/16 01:45:01 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		xbiggery(t_set *set, int color)
{
	set->line.y = set->line.y0;
	set->line.x = set->line.x0;
	set->line.tmp = set->line.deltay > 0 ? 1 : -1;
	set->line.direction = set->line.deltay != 0 ? set->line.tmp : 0;
	while (set->line.deltax > 0 ? set->line.x <=
	set->line.x1 : set->line.x >= set->line.x1)
	{
		my_mlx_pixel_put(set, set->line.x, set->line.y, color);
		set->line.accrection += set->line.abs_deltay;
		if (set->line.accrection >= set->line.abs_deltax)
		{
			set->line.accrection -= set->line.abs_deltax;
			set->line.y += set->line.direction;
		}
		set->line.deltax > 0 ? set->line.x++ : set->line.x--;
	}
}

static void		ybiggerx(t_set *set, int color)
{
	set->line.y = set->line.y0;
	set->line.x = set->line.x0;
	set->line.tmp = set->line.deltax > 0 ? 1 : -1;
	set->line.direction = set->line.deltax != 0 ? set->line.tmp : 0;
	while (set->line.deltay > 0 ? set->line.y <=
	set->line.y1 : set->line.y >= set->line.y1)
	{
		my_mlx_pixel_put(set, set->line.x, set->line.y, color);
		set->line.accrection += set->line.abs_deltax;
		if (set->line.accrection >= set->line.abs_deltay)
		{
			set->line.accrection -= set->line.abs_deltay;
			set->line.x += set->line.direction;
		}
		set->line.deltay > 0 ? set->line.y++ : set->line.y--;
	}
}

void			draw_line(t_set *set, int color)
{
	set->line.deltax = set->line.x1 - set->line.x0;
	set->line.deltay = set->line.y1 - set->line.y0;
	set->line.abs_deltax = abs(set->line.deltax);
	set->line.abs_deltay = abs(set->line.deltay);
	set->line.accrection = 0;
	if (set->line.abs_deltax >= set->line.abs_deltay)
		xbiggery(set, color);
	else
		ybiggerx(set, color);
}
