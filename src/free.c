/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/04/07 09:01:33 by rcarmen          ###   ########.fr       */
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

void			free_map(t_set *set)
{
	int i;

	i = 0;
	while (i < set->tabs.map_h)
	{
		free(((t_set *)set)->scene.map[i]);
		i++;
	}
	free(((t_set *)set)->scene.map);
}

void			free_scene(t_set *set)
{
	free(((t_set *)set)->scene.ea_t);
	free(((t_set *)set)->scene.we_t);
	free(((t_set *)set)->scene.so_t);
	free(((t_set *)set)->scene.no_t);
	free(((t_set *)set)->scene.spr_t);
}

void			free_textures(t_set *set)
{
	int i;

	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(set->mlx.mlx, set->texture[i].img);
		i++;
	}
}
