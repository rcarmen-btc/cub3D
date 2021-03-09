/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/11 02:40:32 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			free_param_split(char **param_split, int n)
{
	int			i;

	i = 0;
	while (i < n)
	{
		ft_memdel(&(*(param_split + i)));
		i++;
	}
	free(param_split);
}

void			free_content(void *content)
{
	free(content);
	content = NULL;
}

void			free_scene(t_set *set)
{
	int i;

	free(((t_set *)set)->scene.ea_t);
	free(((t_set *)set)->scene.we_t);
	free(((t_set *)set)->scene.so_t);
	free(((t_set *)set)->scene.no_t);
	free(((t_set *)set)->scene.spr_t);
	i = 0;
	while (i < set->tabs.map_h)
	{
		free(((t_set *)set)->scene.map[i]);
		i++;
	}
	free(((t_set *)set)->scene.map);
}

void			free_mlx(t_set *set)
{
	mlx_clear_window(((t_set *)set)->mlx.mlx, ((t_set *)set)->mlx.win);
	mlx_destroy_image(((t_set *)set)->mlx.mlx, ((t_set *)set)->mlx.img);
	mlx_destroy_window(((t_set *)set)->mlx.mlx, ((t_set *)set)->mlx.win);
	mlx_destroy_display(((t_set *)set)->mlx.mlx);
	free(((t_set *)set)->mlx.mlx);
}

void			free_tabs(t_set *set)
{
	free(set->tabs.fsint);
	free(set->tabs.fisint);
	free(set->tabs.fcost);
	free(set->tabs.ficost);
	free(set->tabs.ftant);
	free(set->tabs.fitant);
	free(set->tabs.ffisht);
	free(set->tabs.fxstept);
	free(set->tabs.fystept);
}