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

#ifndef MAIN_H
# define MAIN_H
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# define PI 3.14159265359

#include <stdio.h>

typedef struct		s_kfl
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
}					t_kfl;


typedef struct		s_pattr
{
	int				fpx;
	int				fpy;
	int				fpa;
	int				fpdtopp;
	int				fph;
	int				fpseed; 
	int				fppycen;
	float			playerxd;
	float			playeryd;
}					t_pattr;

typedef struct		s_ray
{
	int				tile_size;
	int				wall_height;
	int				angle60;
	int				angle30;
	int				angle15;
	int				angle90;
	int				angle180;
	int				angle270;
	int				angle360;
	int				angle0;
	int				angle5;
	int				angle10;
	int				ppw;
	int				pph;
	int				verticalgrid;
	int				horizontalgrid;
	int				ditoneverg;
	int				ditonehorg;
	float			xinter;
	float			yinter;
	float			ditonexinter;
	float			ditoneyinter;
	int				x_grid_index;
	int				y_grid_index;
	float			ditovergrbehit;
	float			ditohorgrbehit;
	int				castarc;
	int				castcolumn;
	float			dist;
	int				projwhei;
	int				topOfWall;
	int				bottomOfWall;
	float			xtemp;
	float			ytemp;
	int				forhook;
}					t_ray;

typedef struct		s_line
{
	int 			deltax;
	int 			deltay;
	int 			abs_deltax;
	int 			abs_deltay;
	int 			x;
	int 			y;
	int 			x0;
	int 			y0;
	int 			x1;
	int 			y1;
	int 			accrection;
	int 			tmp;
	int 			direction; 
}					t_line;

typedef struct		s_tabs
{
	float			*fsint;
	float			*fisint;
	float			*fcost;
	float			*ficost;
	float			*ftant;
	float			*fitant;
	float			*ffisht;
	float			*fxstept;
	float			*fystept;
  	int				map_h;
  	int				map_w;
}					t_tabs;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				ll;
	int				en;
}					t_mlx;

typedef struct		s_scene
{
	int				rxy[4];
	int				drxy[2];
	char			*no_t;
	char			*so_t;
	char			*we_t;
	char			*ea_t;
	char			*spr_t;
	unsigned char	f_rgb[3];
	unsigned char	c_rgb[3];
	char			**map;
	int				save;
	int				sprnum;
}					t_scene;

typedef struct		s_rect
{
	int				color;	
	int				w;
	int				h;
	int				x;
	int				y;
	int				xoffset;
	float			ty_step;
	float			ty_off;
	float			ty;
	float			tx;
	int				tnum;
	int				side;
}					t_rect;

typedef struct		s_sprite
{
	int				id;
	int				is_visible;
	int				x;
	int				y;
	int				row;
	int				col;
	int				dx;
	int				dy;
	float			dist;
	char			*tex;
	float			start_y;
	float			end_y;
	float			right_x;
	float			left_x;
	float			angle;
	float			height;
	float			width;
}					t_sprite;



typedef struct		s_set
{
	t_pattr			pattr;
	t_line			line;
	t_mlx			mlx;
	t_scene			scene;
	t_ray			ray;
	t_tabs			tabs;
	t_mlx			texture[5];
	t_kfl			kfl;
	t_sprite		*sprite;
}					t_set;

int					where_player(t_set *set, char c, int x, int y);
void				init_sprite(t_set *set);
unsigned int		pixel_color(t_set *set, int x, int y ,int tnum);
void				parsing_scene(char **av, t_set *set);
float				arcToRad(float arcAngle, t_set *set);
void				set_rgb_params(t_set *set, char *parse_rgb, char fc);
void				get_texture(t_set *set);
void				alloc_tabs(t_set *set);
void				free_param_split(char **param_split, int n);
void				free_content(void *content);
void				print_square(t_set *set, int x, int y, int color);
void				find_player(t_set *set);
//void				isvalid_map(t_params *params);
void				additional_condition(t_set *set, int i);
int					key_press_hook(int keycode, t_set *set);
int					create_trgb(int t, int r, int g, int b);
int					key_release_hook(int keycode, t_set *set);
void				free_tabs(t_set *set);
int					exit_hook(void *data);
void				my_mlx_pixel_put(t_set *set, int x, int y, int color);
// void				print_player(t_set *set, int sizex, int sizey, int color);
void				draw_background(t_set *set);
void				draw_sprites(t_set *set);
void				smooth_move(t_set *set);
void				init(t_set *set);
void				free_mlx(t_set *set);
void				init_ray(t_set *set);
void				print_map(t_set *set);
void				draw_line(t_set *set, int color);
void				raycasting(t_set *set);
void				myerror(char *mess, int err_code, t_set *set);
void				isvalid_arg(int ac, char **av, t_set *set);
void				filltexrect(t_set *set, t_rect rect);
void				draw_line_tex(t_set *set, t_rect rect);
void				fillrect(t_set *set, t_rect rect);
void				free_scene(t_set *set);
void				sortspr(t_set *set);

#endif
