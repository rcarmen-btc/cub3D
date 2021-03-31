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
	free(set->scene.dist_be_hit);
}

void			free_sprite(t_set *set)
{
	free(set->sprite);
}
