/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/03/31 11:49:08 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void				init_bitmap(char *bmp, t_set *set)
{
	bmp[0] = 'B';
	bmp[1] = 'M';
	bmp[10] = (unsigned char)54;
	bmp[14] = (unsigned char)40;
	bmp[18] = (unsigned char)set->scene.rxy[0];
	bmp[19] = (unsigned char)(set->scene.rxy[0] >> 8);
	bmp[20] = (unsigned char)(set->scene.rxy[0] >> 16);
	bmp[21] = (unsigned char)(set->scene.rxy[0] >> 24);
	bmp[22] = (unsigned char)set->scene.rxy[1];
	bmp[23] = (unsigned char)(set->scene.rxy[1] >> 8);
	bmp[24] = (unsigned char)(set->scene.rxy[1] >> 16);
	bmp[25] = (unsigned char)(set->scene.rxy[1] >> 24);
	bmp[26] = (unsigned char)(1);
	bmp[28] = (unsigned char)(32);
}

void				draw_pixels(char *bmp, t_set *set)
{
	int	i;
	int	j;
	int k;
	int addr_index;

	k = 0;
	i = set->scene.rxy[1];
	while (--i)
	{
		j = -1;
		while (++j < set->scene.rxy[0])
		{
			addr_index = (i * set->mlx.ll + j * 4);
			bmp[k * 4] = *(int *)(set->mlx.addr + addr_index);
			bmp[k * 4 + 1] = (*(int *)(set->mlx.addr + addr_index) >> 8);
			bmp[k * 4 + 2] = (*(int *)(set->mlx.addr + addr_index) >> 16);
			bmp[k * 4 + 3] = (unsigned char)0xFF;
			k++;
		}
	}
}

void				save_bitmap(t_set *set)
{
	char			*bmp;
	int				fd;
	int				pixels;

	if ((fd = open("screenshot.bmp", O_RDWR | O_CREAT, 0666)) < 0)
		myerror("Error\nThe file doesn't open.\n", 0, set);
	pixels = set->scene.rxy[0] * set->scene.rxy[1];
	if (NULL == (bmp = (char *)ft_calloc(54 + pixels * 4, sizeof(int))))
		myerror("Error\nft_calloc in file save.c.\n", 0, set);
	init_bitmap(bmp, set);
	draw_pixels(bmp + 54, set);
	if (write(fd, bmp, 54 + pixels * 4) < 0)
	{
		close(fd);
		free(bmp);
		myerror("Error\n", 0, set);
	}
	free(bmp);
	close(fd);
}
