/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/10 11:16:28 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "main.h"

void			set_rgb_params(t_params *params, char *parse_rgb, char fc)
{
	int i;
	char **split_rgb;
	unsigned char *fc_rgb;

	i = 0;
	split_rgb = ft_split(parse_rgb, ',');	
	fc_rgb = fc == 'f' ? params->f_rgb : params->c_rgb;
	while (i < 3)
	{
		fc_rgb[i] = ft_atoi(*(split_rgb + i));
		i++;
	}
	free_param_split(split_rgb, 3);
}