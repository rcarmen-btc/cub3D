#include "main.h"

void			get_texture(t_set *set)
{
	int w, h;
	set->texture[0].img = mlx_xpm_file_to_image(set->mlx.mlx, "zz.xpm", &w, &h);
	set->texture[0].addr = mlx_get_data_addr(set->texture[0].img, &(set->texture[0].bpp),
	&(set->texture[0].ll), &(set->texture[0].en));
}