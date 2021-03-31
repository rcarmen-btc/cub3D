/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/18 07:30:36 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char				find_substr_no_alloc(char *line, char *substr)
{
	char			*tmp;

	if (NULL != (tmp = ft_strnstr(line, substr, 3)))
		return (1);
	return (0);
}

void				isfullparam(t_set set, char *line)
{
	if (0 != (find_substr_no_alloc(line, "R ")))
	{
		if (set.scene.rxy[0] != 0 && set.scene.rxy[1] != 0)
			myerror("Error\nTwo or more R param.\n", 0, &set);
		return ;
	}
	else if (0 != (find_substr_no_alloc(line, "NO ")) && NULL != set.scene.no_t)
		myerror("Error\nTwo or more NO param.\n", 0, &set);
	else if (0 != (find_substr_no_alloc(line, "SO ")) && NULL != set.scene.so_t)
		myerror("Error\nTwo or more SO param.\n", 0, &set);
	else if (0 != (find_substr_no_alloc(line, "WE ")) && NULL != set.scene.we_t)
		myerror("Error\nTwo or more WE param.\n", 0, &set);
	else if (0 != (find_substr_no_alloc(line, "EA ")) && NULL != set.scene.ea_t)
		myerror("Error\nTwo or more EA param.\n", 0, &set);
	else if (0 != (find_substr_no_alloc(line, "S ")) && NULL != set.scene.spr_t)
		myerror("Error\nTwo or more S param.\n", 0, &set);
	else if (0 != (find_substr_no_alloc(line, "F ")) &&
	-1 != set.scene.f_rgb[1])
		myerror("Error\nTwo or more F param.\n", 0, &set);
	else if (0 != (find_substr_no_alloc(line, "C ")) &&
	-1 != set.scene.c_rgb[1])
		myerror("Error\nTwo or more C param.\n", 0, &set);
}

void				parsing_params(int *ps, char *line, t_set *set)
{
	char			**param_split;
	int				i;
	int				j;

	i = 1;
	if (NULL != (param_split = find_substr(line, "R ", ps)))
	{
		get_wrd_cnt(line, ' ') > 3 ? myerror("Error\nInvalid R\n", 0, set) : 0;
		while (i < 3)
		{
			j = 0;
			while (param_split[i][j] != '\0')
			{
				if (ft_isalpha(param_split[i][j]))
					myerror("Error\nInvalid R param.\n", 0, set);
				j++;
			}
			i++;
		}
		set->scene.rxy[0] = ft_atoi(*(param_split + 1));
		set->scene.rxy[1] = ft_atoi(*(param_split + 2));
		free_param_split(param_split, 3);
		return ;
	}
	utils(ps, line, param_split, set);
}
