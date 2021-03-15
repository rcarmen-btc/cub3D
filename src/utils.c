/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/17 12:59:34 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void					alloc_tabs(t_set *set)
{
	set->tabs.fsint = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fisint = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fcost = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.ficost = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.ftant = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fitant = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.ffisht = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fxstept = ft_calloc(set->ray.angle360 + 1, sizeof(float));
	set->tabs.fystept = ft_calloc(set->ray.angle360 + 1, sizeof(float));
}

void					additional_condition(t_set *set, int i)
{
	if (i >= set->ray.angle0 && i < set->ray.angle180)
	{
		set->tabs.fystept[i] = (float)(set->ray.tile_size *
		set->tabs.ftant[i]);
		if (set->tabs.fystept[i] < 0)
			set->tabs.fystept[i] = -set->tabs.fystept[i];
	}
	else
	{
		set->tabs.fystept[i] = (float)(set->ray.tile_size *
		set->tabs.ftant[i]);
		if (set->tabs.fystept[i] > 0)
			set->tabs.fystept[i] = -set->tabs.fystept[i];
	}
}
