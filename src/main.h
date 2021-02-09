/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/10 00:15:42 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "libft.h"
# include "mlx.h"
#include <fcntl.h>

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_params
{
	int				resol_xy[2];
	int				def_resol_xy[2];
	char			*no_t;
	char			*so_t;
	char			*we_t;
	char			*ea_t;
	char			*sprite_t;
	unsigned char	f_rgb[3];
	unsigned char	c_rgb[3];
}					t_params;

void				parsing_scene(int fd, t_params *params);

#endif
