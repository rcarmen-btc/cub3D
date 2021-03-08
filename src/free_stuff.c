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
