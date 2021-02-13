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

void			print_rectangle(t_data *data, int sizex, int sizey, int color)
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