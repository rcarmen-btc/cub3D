/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/16 01:54:29 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "linux_kcode.h"

int			key_press_hook(int keycode, t_data *data)
{
	if (keycode == MLX_KEY_D && data->px + 5 <= data->drxy[0])
		data->px += 5;
	else if (keycode == MLX_KEY_A && data->px - 5 >= 0)
		data->px -= 5;
	else if (keycode == MLX_KEY_W && data->py - 5 >= 0)
		data->py -= 5;
	else if (keycode == MLX_KEY_S && data->py + 5 <= data->drxy[1])
		data->py += 5;
	else if (keycode == MLX_KEY_LEFT)
	{
		data->pa -= 0.1;
		data->pa += (data->pa < 0) ? 2 * PI : 0;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	else if (keycode == MLX_KEY_RIGHT)
	{
		data->pa += 0.1;
		data->pa += (data->pa < 0) ? 2 * PI : 0;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	return (0);
}

int			exit_hook(void *data)
{
	int		i;

	mlx_clear_window(((t_data *)data)->mlx, ((t_data *)data)->win);
	mlx_destroy_image(((t_data *)data)->mlx, ((t_data *)data)->img);
	mlx_destroy_window(((t_data *)data)->mlx, ((t_data *)data)->win);
	mlx_destroy_display(((t_data *)data)->mlx);
	free(((t_data *)data)->mlx);
	free(((t_data *)data)->ea_t);
	free(((t_data *)data)->we_t);
	free(((t_data *)data)->so_t);
	free(((t_data *)data)->no_t);
	free(((t_data *)data)->spr_t);
	i = 0;
	while (i < 15)
	{
		free(((t_data *)data)->map[i]);
		i++;
	}
	free(((t_data *)data)->map);
	free((t_data *)data);
	exit(0);
}
