#include "main.h"
#include "linux_kcode.h"

int			key_press_hook(int keycode, t_data *data)
{
	if (keycode == MLX_KEY_D && data->x + 5 <= data->drxy[0])
		data->x += 5;
	else if (keycode == MLX_KEY_A && data->x - 5>= 0)
		data->x -= 5;
	else if (keycode == MLX_KEY_W && data->y - 5 >= 0)
		data->y -= 5;
	else if (keycode == MLX_KEY_S && data->y + 5 <= data->drxy[1])
		data->y += 5;
	return (0);
}

int			exit_hook(void *data)
{
/*
**
** - What time is it?
**
** - Time to free up memory!!!
**
*/
	mlx_clear_window(((t_data *)data)->mlx, ((t_data *)data)->win);
	mlx_destroy_image(((t_data *)data)->mlx, ((t_data *)data)->img);
	mlx_destroy_window(((t_data *)data)->mlx, ((t_data *)data)->win);
	mlx_destroy_display(((t_data *)data)->mlx);
	free(((t_data *)data)->ea_t);
	free(((t_data *)data)->we_t);
	free(((t_data *)data)->so_t);
	free(((t_data *)data)->no_t);
	free(((t_data *)data)->spr_t);
	int i = 0;
	while (i < 15)
	{
		free(((t_data *)data)->map[i]);
		i++;
	}
	free(((t_data *)data)->map);
	free((t_data *)data);	

	exit(0);
}