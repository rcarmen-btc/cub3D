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
	int				i[2];
	char			**split_rgb;
	int	*fc_rgb;
	int cnt;

	i[0] = 0;
	cnt = get_wrd_cnt(parse_rgb, ',');
	split_rgb = ft_split(parse_rgb, ',');
	if (cnt != 3)
		myerror("Error\nToo few or too much color param\n", 0, set);
	fc_rgb = fc == 'f' ? set->scene.f_rgb : set->scene.c_rgb;
	while (i[0] < 3)
	{
		i[1] = 0;
		while (split_rgb[i[0]][i[1]] != '\0')
		{
			if (ft_isalpha(split_rgb[i[0]][i[1]]))
				myerror("Error\nInvalid C or F param\n", 0, set);	
			i[1]++;
		}
		fc_rgb[i[0]] = ft_atoi(*(split_rgb + i[0]));
		if (fc_rgb[i[0]] > 255 || fc_rgb[i[0]] < 0)
			myerror("Error\nParam F or C most be in range 0-255\n", 0, set);
		i[0]++;
	}
	free_param_split(split_rgb, 3);
}

void				check_trgb(t_set *set)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (set->scene.c_rgb[i] == -1)
			myerror("Error\nToo few or too much color param.\n", 0, set);
		if (set->scene.f_rgb[i] == -1)
			myerror("Error\nToo few or too much color param.\n", 0, set);
		i++;
	}
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
