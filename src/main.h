/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/14 16:23:28 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>

#include <stdio.h>

//# define 
typedef struct		s_player
{
	float				x;
	float				y;
	
}					t_player;

typedef struct		s_data
{
	//float				x;
	//float				y;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				ll;
	int				en;
	int				rxy[2];
	int				drxy[2];
	char			*no_t;
	char			*so_t;
	char			*we_t;
	char			*ea_t;
	char			*spr_t;
	unsigned char	f_rgb[3];
	unsigned char	c_rgb[3];
	char			**map;
}					t_data;

void				parsing_scene(char **av, t_data *data);
void				set_rgb_params(t_data *params, char *parse_rgb, char fc);
void				free_param_split(char **param_split, int n);
void				free_content(void *content);
//void				isvalid_map(t_params *params);
int					key_press_hook(int keycode, t_data *data);
int					exit_hook(void *data);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				print_player(t_data *data, int sizex, int sizey, int color);
void				print_background(t_data *data, int color);
void				print_map(t_data *data);

#endif
