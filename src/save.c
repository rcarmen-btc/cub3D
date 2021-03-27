#include "main.h"

// void			get_rgb(t_set *set, int x, int y)
// {
// 	char		*dst;
// 	int			color;

// 	dst = set->mlx.addr + (y * set->mlx.ll + x * (set->mlx.bpp / 8));
// 	color = *(unsigned int *)dst;
// 	set->rgb.red = (color & 0xFFFF00) >> 16;
// 	set->rgb.green = (color & 0xFF00) >> 8;
// 	set->rgb.blue = (color & 0xFF);
// }

// void			save_bitmap(t_set *set, t_bmp bmp)
// {	
// 	int fd;
// 	// int x;
// 	int z;

// 	(void)set;
// 	(void)z;
// 	fd = open("playground.bmp", O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
// 	z = write(fd, bmp.file_type, 2);
// 	z = write(fd, &bmp.file_size, 4);
// 	z = write(fd, &bmp.reserved, 4);
// 	z = write(fd, &bmp.pd_offset, 4);
// 	z = write(fd, &bmp.h_size, 4);
// 	z = write(fd, &bmp.img_w, 4);
// 	z = write(fd, &bmp.img_h, 4);
// 	z = write(fd, &bmp.plane, 4);
// 	z = write(fd, &bmp.bpp, 4);
// 	z = write(fd, &bmp.compr, 4);
// 	z = write(fd, &bmp.img_size, 4);
// 	z = write(fd, &bmp.xppm, 4);
// 	z = write(fd, &bmp.yppm, 4);
// 	z = write(fd, &bmp.total_color, 4);
// 	z = write(fd, &bmp.imp_color, 4);

	
// 	// int y;
// 	// unsigned char pix_col[3];
// 	// y = bmp.img_h - 1;
// 	// while (y >= 0)
// 	// {
// 	// 	x = 0;
// 	// 	while (x < bmp.img_w)
// 	// 	{
// 	// 		get_rgb(set, x, y);
// 	// 		pix_col[0] = set->rgb.blue;
// 	// 		pix_col[1] = set->rgb.green;
// 	// 		pix_col[3] = set->rgb.red;
// 	// 		write(fd, pix_col, 3);
// 	// 		// z = write(fd, &rgb.blue, 1);
// 	// 		// z = write(fd, &rgb.green, 1);
// 	// 		// z = write(fd, &rgb.red, 1);
// 	// 		x++;
// 	// 	}
// 	// 	ft_bzero(pix_col, 3);
// 	// 	write(fd, pixel_color, offset);
// 	// 	y--;		
// 	// }
	
// }

void		init_bitmap(char *bmp, t_set *set)
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
	bmp[28] = (unsigned char)(32);;

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
		while (++j <set->scene.rxy[0])
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
	
	if ((fd = open("screenshot.bmp",  O_RDWR | O_CREAT, 0666)) < 0)
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