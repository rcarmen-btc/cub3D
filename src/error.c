/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/04/07 09:01:26 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		myerror(char *mess, int err_code, t_set *set)
{
	int		r;

	(void)r;
	r = write(2, mess, ft_strlen(mess));
	if (err_code == 1)
		free_mlx(set);
	else if (err_code == 2)
	{
		free_mlx(set);
		free_scene(set);
		free_tabs(set);
	}
	else if (err_code == 3)
	{
		free_scene(set);
		free_tabs(set);
	}
	else if (err_code == 4)
		free(((t_set *)set)->mlx.mlx);
	else if (err_code == 5)
		free_scene(set);
	exit(0);
}
