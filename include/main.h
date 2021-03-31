/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/03/31 11:42:03 by rcarmen          ###   ########.fr       */
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
# define CLOSE "Error\nScene the file does not close.\n"
# define INV "Error\nInvalid map.\n"
# define COUNT "Error\nInvalid conut of param.\n" 
# define MLX_KEY_A              97
# define MLX_KEY_S              115
# define MLX_KEY_D              100
# define MLX_KEY_W              119
# define MLX_KEY_LEFT           65361
# define MLX_KEY_RIGHT          65363
# define MLX_KEY_SHIFT_L        65505
# define MLX_KEY_ESCAPE         65307

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
	int				rxy[2];
	int				drxy[2];
	char			*no_t;
	char			*so_t;
	char			*we_t;
	char			*ea_t;
	char			*spr_t;
	int				f_rgb[3];
	int				c_rgb[3];
	char			**map;
	char			**map_arr;
	int				save;
	int				sprnum;
	int				*dist_be_hit;
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

typedef struct		s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_rgb;

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



typedef struct	s_bmp
{
	unsigned char		file_type[2];
	int					file_size;
	unsigned int		reserved;
	int					pd_offset;
	int					h_size;
	int					img_w;
	int					img_h;
	int					plane;
	int					bpp;
	int					compr;
	int					img_size;
	int					xppm;
	int					yppm;
	int					total_color;
	int					imp_color;
}				t_bmp;

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
	t_bmp			bmp;
	t_rgb			rgb;
	int 			start_index_x;
	int 			start_index_y;
	int 			n;
	int 			ntek;
	int 			arr1[2];
	int 			arr2[2];
	int 			max;
	int 			i;
	int 			*mx;
	int 			*my;
}					t_set;


int					in_arr(int arr1[], int arr2[], int ind1, int ind2);
// void				parsing_map(t_list **map_lines, t_set *set);
int					is_valid_tile(char c);
int					is_in_map(char c);
void				*ft_onealloc(size_t nmemb, size_t size);
void				parsing_params(int *ps, char *line, t_set *set);
void				utils(int *ps, char *line, char **param_split, t_set *set);
void				init_sprite_utils(t_set *set, int *s, int *x, int *y);
void				sprite_utils(t_set *set, int *s, int *i, int *j);
void				isfullparam(t_set set, char *line);
char				find_substr_no_alloc(char *line, char *substr);
char				**find_substr(char *line, char *substr, int *ps);
void				get_texture_utils(t_set *set);
void				free_map(t_set *set);
void				save_bitmap(t_set *set);
void				init_tabs(t_set *set);
float				get_distance(float x1, float y1, float x2, float y2);
void				floodfill(t_set *set);
void				init_flood(t_set *set);
void				get_spr_val(t_set *set, t_sprite *spr);
void				init_pattr(t_set *set);
void				free_textures(t_set *set);
int					where_player(t_set *set, char c, int x, int y);
int					get_wrd_cnt(char const *s, char c);
void				init_sprite(t_set *set);
unsigned int		pixel_color(t_set *set, int x, int y ,int tnum);
void				parsing_scene(char **av, t_set *set);
void				init_mlx(t_set *set);
float				arcToRad(float arcAngle, t_set *set);
void				set_rgb_params(t_set *set, char *parse_rgb, char fc);
void				get_texture(t_set *set);
float				in_two_pi_range(float rad);
int					ft_s_color(t_set *set, t_sprite sprite, int x, int y);
void					draw_sprite(t_set *set, t_sprite sprite,
int xoffset, int yoffset);
void				free_sprite(t_set *set);
void				alloc_tabs(t_set *set);
void				free_param_split(char **param_split, int n);
void				free_content(void *content);
void				print_square(t_set *set, int x, int y, int color);
void				init_before_parse(t_set *set);
void				find_player(t_set *set);
void				isvalid_map(t_set *set);
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
void				init_after_parse(t_set *set);
void				check_trgb(t_set *set);
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
