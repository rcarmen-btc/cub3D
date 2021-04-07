/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/04/07 09:02:20 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int					check_comma(char *parse_rgb, t_set *set)
{
	int				i;
	int				comma_cnt;

	i = 0;
	comma_cnt = 0;
	while (parse_rgb[i] != '\0')
	{
		if (parse_rgb[i] == ',')
			comma_cnt++;
		i++;
	}
	if (comma_cnt != 2)
		myerror("Error\nInvalid color(F, C) param.\n", 0, set);
	return (get_wrd_cnt(parse_rgb, ','));
}

void				set_rgb_params(t_set *set, char *parse_rgb, char fc)
{
	int				i[2];
	char			**split_rgb;
	int				*fc_rgb;
	int				cnt;

	i[0] = 0;
	cnt = check_comma(parse_rgb, set);
	split_rgb = ft_split(parse_rgb, ',');
	(cnt != 3) ? myerror("Error\nInvalid color param\n", 0, set) : 0;
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
	char *dst;

	dst = set->texture[tnum].addr + (y * set->texture[tnum].ll) + (x * 4);
	return (*(unsigned*)dst);
}

int					create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
