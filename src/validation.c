/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/03/31 11:42:56 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void				init_flood(t_set *set)
{
	set->start_index_x = set->pattr.fpx / 64;
	set->start_index_y = set->pattr.fpy / 64;
	set->arr1[0] = 2;
	set->arr2[0] = 6;
	set->arr1[1] = -1;
	set->arr2[1] = -1;
	if (set->tabs.map_w > set->tabs.map_h)
		set->max = set->tabs.map_w;
	else
		set->max = set->tabs.map_h;
	set->mx = (int *)ft_onealloc(set->max * set->max + 1, sizeof(int));
	set->my = (int *)ft_onealloc(set->max * set->max + 1, sizeof(int));
	set->i = 0;
	set->n = 0;
	set->ntek = -1;
	set->mx[0] = set->start_index_x;
	set->my[0] = set->start_index_y;
	set->i = 0;
}

void				*ft_onealloc(size_t nmemb, size_t size)
{
	char	*mem;

	if (!(mem = malloc(nmemb * size)))
		return (NULL);
	return (ft_memset(mem, -1, nmemb * size));
}

void				isvalid_map(t_set *set)
{
	int i;

	i = 0;
	while (set->scene.map[0][i] != '\0')
		if (is_in_map(set->scene.map[0][i++]))
			myerror("Error\n0 contacts the void or the wall is missing.\n",
			0, set);
	i = 0;
	while (set->scene.map[set->tabs.map_h - 1][i] != '\0')
		if (set->scene.map[set->tabs.map_h - 1][i++] != '1')
			myerror("Error\n0 contacts the void or the wall is missing.\n",
			0, set);
	floodfill(set);
}
