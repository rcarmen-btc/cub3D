/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/04/07 11:41:59 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			up_side(t_set *set)
{
	if (is_in_map(set->scene.map[set->my[set->ntek] - 1]
	[set->mx[set->ntek]]))
	{
		if (in_arr(set->my, set->mx, set->my[set->ntek] - 1,
		set->mx[set->ntek]))
		{
			set->n++;
			set->my[set->n] = set->my[set->ntek] - 1;
			set->mx[set->n] = set->mx[set->ntek];
		}
		else if (is_valid_tile(set->scene.map[set->my[set->ntek] - 1]
		[set->mx[set->ntek]]))
			myerror("Error\n0 contacts the void or the wall is missing..\n",
			0, set);
	}
	else if (is_valid_tile(set->scene.map[set->my[set->ntek] -
	1][set->mx[set->ntek]]))
		myerror("Error\n0 contacts the void.\n", 0, set);
}

static void			down_side(t_set *set)
{
	if (is_in_map(set->scene.map[set->my[set->ntek] + 1]
	[set->mx[set->ntek]]))
	{
		if (in_arr(set->my, set->mx, set->my[set->ntek] + 1,
		set->mx[set->ntek]))
		{
			set->n++;
			set->my[set->n] = set->my[set->ntek] + 1;
			set->mx[set->n] = set->mx[set->ntek];
		}
		else if (is_valid_tile(set->scene.map[set->my[set->ntek] + 1]
		[set->mx[set->ntek]]))
			myerror("Error\n0 contacts the void or the wall is missing..\n",
			0, set);
	}
	else if (is_valid_tile(set->scene.map[set->my[set->ntek] +
	1][set->mx[set->ntek]]))
		myerror("Error\n0 contacts the void.\n", 0, set);
}

static void			left_side(t_set *set)
{
	if (is_in_map(set->scene.map[set->my[set->ntek]]
	[set->mx[set->ntek] - 1]))
	{
		if (in_arr(set->my, set->mx, set->my[set->ntek],
		set->mx[set->ntek] - 1))
		{
			set->n++;
			set->my[set->n] = set->my[set->ntek];
			set->mx[set->n] = set->mx[set->ntek] - 1;
		}
		else if (is_valid_tile(set->scene.map[set->my[set->ntek]]
		[set->mx[set->ntek] - 1]))
			myerror("Error\n0 contacts the void or the wall is missing..\n",
			0, set);
	}
	else if (is_valid_tile(set->scene.map[set->my[set->ntek]]
	[set->mx[set->ntek] - 1]))
		myerror("Error\n0 contacts the void or the wall is missing..\n",
		0, set);
}

static void			right_side(t_set *set)
{
	if (is_in_map(set->scene.map[set->my[set->ntek]]
	[set->mx[set->ntek] + 1]))
	{
		if (in_arr(set->my, set->mx, set->my[set->ntek],
		set->mx[set->ntek] + 1))
		{
			set->n++;
			set->my[set->n] = set->my[set->ntek];
			set->mx[set->n] = set->mx[set->ntek] + 1;
		}
		else if (is_valid_tile(set->scene.map[set->my[set->ntek]]
		[set->mx[set->ntek] + 1]))
			myerror("Error\n0 contacts the void or the wall is missing.\n",
			0, set);
	}
	else if (is_valid_tile(set->scene.map[set->my[set->ntek]]
	[set->mx[set->ntek] + 1]))
		myerror("Error\n0 contacts the void or the wall is missing.\n",
		0, set);
}

void				floodfill(t_set *set)
{
	init_flood(set);
	while (set->ntek != set->n || set->i == 0)
	{
		set->i = 1;
		set->ntek++;
		up_side(set);
		down_side(set);
		left_side(set);
		right_side(set);
	}
	free(set->mx);
	free(set->my);
}
