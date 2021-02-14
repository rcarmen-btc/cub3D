#include "main.h"

void			print_background(t_data *data, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < data->drxy[0])
	{
		while (y < data->drxy[1])
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
}

void			print_player(t_data *data, int sizex, int sizey, int color)
{
	int x; 
	int y;
	int k; 
	int n;

	x = data->x;
	y = data->y;
	k = x + sizex;
	n = y + sizey;
	while (x < k)
	{
		while (y < n)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		y = data->y;
		x++;
	}
}

void			print_square(t_data *data, int x, int y, int color)
{
	int k;
	int n;
	//int start_x;
	int start_y;

	//start_x = x;
	start_y = y;
	k = x + 20;
	n = y + 20;
	while (x < k)
	{
		while (y < n)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		y = start_y;
		x++;
	}
}

void			print_map(t_data *data)
{
	int x;
	int y;
	int sqr_s;
	int color;

	x = 0;
	y = 0;
	sqr_s = 20;
	color = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0')
				color = 0x00000000;
			else
				color = 0x00FFFFFF;
			print_square(data, x * sqr_s, y * sqr_s, color);
			x++;
		}
		x = 0;
		y++;
	}
	
}