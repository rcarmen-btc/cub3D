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

	x = data->px;
	y = data->py;
	k = x + sizex;
	n = y + sizey;
	while (x < k)
	{
		while (y < n)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		y = data->py;
		x++;
	}
	x = data->px;
	y = data->py;
	
	print_line(data, data->px, data->py, data->px+data->pdx*5, data->py+data->pdy*5);
	

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
				color = 0x0044C5C;
			else
				color = 0x00E1B16A;
			print_square(data, x * sqr_s, y * sqr_s, color);
			x++;
		}
		x = 0;
		y++;
	}
	
}

void			print_line(t_data *data, float x0, float y0, float x1, float y1)
{
	int deltax;
	int deltay;
	int abs_deltax;
	int abs_deltay;
	int x;
	int y;

	deltax = x1 - x0;
	deltay = y1 - y0;

	abs_deltax = abs(deltax);
	abs_deltay = abs(deltay);
	int accrection = 0;

	if (abs_deltax >= abs_deltay)
	{
		y = y0;
		x = x0;
		int tmp = deltay > 0 ? 1 : -1;
		int direction = deltay != 0 ? tmp : 0; 
		while (deltax > 0 ? x <= x1 : x >= x1)
		{
			my_mlx_pixel_put(data, x, y, 0xFFFFFFFF);
			accrection += abs_deltay;
			if (accrection >= abs_deltax)
			{
				accrection -= abs_deltax;
				y += direction;
			}
			deltax > 0 ? x++ : x--;
		}
		
	}
	else
	{
		y = y0;
		x = x0;
		int tmp = deltax > 0 ? 1 : -1;
		int direction = deltax != 0 ? tmp : 0; 
		while (deltay > 0 ? y <= y1 : y >= y1)
		{
			my_mlx_pixel_put(data, x, y, 0xFFFFFFFF);
			accrection += abs_deltax;
			if (accrection >= abs_deltay)
			{
				accrection -= abs_deltay;
				x += direction;
			}
			deltay > 0 ? y++ : y--;
		}
		
	}
	
}