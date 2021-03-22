/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/13 17:06:22 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void				set_rgb_params(t_set *set, char *parse_rgb, char fc)
{
	int				i;
	char			**split_rgb;
	unsigned char	*fc_rgb;

	i = 0;
	split_rgb = ft_split(parse_rgb, ',');
	fc_rgb = fc == 'f' ? set->scene.f_rgb : set->scene.c_rgb;
	while (i < 3)
	{
		fc_rgb[i] = ft_atoi(*(split_rgb + i));
		i++;
	}
	free_param_split(split_rgb, 3);
}

unsigned int		pixel_color(t_set *set, int x, int y, int tnum)
{
	// int				index;
	// unsigned int	color;
	// int				octets;
	// int				i;

	// color = 0;
	// i = -1;
	// octets = set->texture[tnum].bpp >> 3;
	// index = (set->texture[tnum].ll * y) + (octets * x);
	// while (++i < octets - 1)
	// 	color += set->texture[tnum].addr[index++] << (i << 3);
	// return (color);
	char *dst;

	dst = set->texture[tnum].addr + (y * set->texture[tnum].ll) + (x * 4);
	return (*(unsigned*)dst);
}

int					create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
