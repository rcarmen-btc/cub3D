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

static void		xbiggery(t_data *data, t_line line, float x1)
{
	float x0;
	float y0;

	x0 = data->px;
	y0 = data->py;
	line.y = y0;
	line.x = x0;
	line.tmp = line.deltay > 0 ? 1 : -1;
	line.direction = line.deltay != 0 ? line.tmp : 0;
	while (line.deltax > 0 ? line.x <= x1 : line.x >= x1)
	{
		my_mlx_pixel_put(data, line.x, line.y, 0xFFFFFFFF);
		line.accrection += line.abs_deltay;
		if (line.accrection >= line.abs_deltax)
		{
			line.accrection -= line.abs_deltax;
			line.y += line.direction;
		}
		line.deltax > 0 ? line.x++ : line.x--;
	}
}

static void		ybiggerx(t_data *data, t_line line, float y1)
{
	float x0;
	float y0;

	x0 = data->px;
	y0 = data->py;
	line.y = y0;
	line.x = x0;
	line.tmp = line.deltax > 0 ? 1 : -1;
	line.direction = line.deltax != 0 ? line.tmp : 0;
	while (line.deltay > 0 ? line.y <= y1 : line.y >= y1)
	{
		my_mlx_pixel_put(data, line.x, line.y, 0xFFFFFFFF);
		line.accrection += line.abs_deltax;
		if (line.accrection >= line.abs_deltay)
		{
			line.accrection -= line.abs_deltay;
			line.x += line.direction;
		}
		line.deltay > 0 ? line.y++ : line.y--;
	}
}

void			print_line(t_data *data, float x1, float y1)
{
	t_line		line;
	float		x0;
	float		y0;

	x0 = data->px;
	y0 = data->py;
	line.deltax = x1 - x0;
	line.deltay = y1 - y0;
	line.abs_deltax = abs(line.deltax);
	line.abs_deltay = abs(line.deltay);
	line.accrection = 0;
	if (line.abs_deltax >= line.abs_deltay)
		xbiggery(data, line, x1);
	else
		ybiggerx(data, line, y1);
}
