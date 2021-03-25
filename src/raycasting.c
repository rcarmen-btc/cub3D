#include "main.h"

float arcToRad(float arcAngle, t_set *set)
{
	return ((float)(arcAngle * PI)/(float)set->ray.angle180);    
}

void	check_tex_rect(t_rect *rect, t_set *set)
{
	if (rect->x > set->scene.rxy[0] - 1)
		rect->x = set->scene.rxy[0] - 1;
	if (rect->y > set->scene.rxy[1] - 1)
		rect->y = set->scene.rxy[1] - 1;
	// if (rect->x + rect->w > set->scene.rxy[1] - 1)
		// rect->w = set->scene.rxy[1] - 1 - rect->x;
	if (rect->h > set->scene.rxy[0] - 1)
		rect->h = set->scene.rxy[1] - 1 - rect->y;
	if (rect->y + rect->h > set->scene.rxy[0] - 1)
		rect->h = set->scene.rxy[1] - 1 - rect->y;

}

void			raycasting(t_set *set)
{
	t_rect rect;

	set->ray.topOfWall = 0;
	set->ray.bottomOfWall = 0;
	set->ray.castarc = set->pattr.fpa;
	set->ray.castarc -= set->ray.angle30;
	if (set->ray.castarc < 0)
		set->ray.castarc += set->ray.angle360;
	for (set->ray.castcolumn = 0; set->ray.castcolumn < set->ray.ppw; set->ray.castcolumn+=1)
	{
		if (set->ray.castarc > set->ray.angle0 && set->ray.castarc < set->ray.angle180)
		{
			set->ray.horizontalgrid = (set->pattr.fpy / set->ray.tile_size) * set->ray.tile_size + set->ray.tile_size;
			set->ray.ditonehorg = set->ray.tile_size;
			set->ray.xtemp = set->tabs.fitant[set->ray.castarc]*(set->ray.horizontalgrid - set->pattr.fpy);
			set->ray.xinter = set->ray.xtemp + set->pattr.fpx;
		}
		else
		{
			set->ray.horizontalgrid = (set->pattr.fpy / set->ray.tile_size) * set->ray.tile_size;
			set->ray.ditonehorg = -set->ray.tile_size;
			set->ray.xtemp = set->tabs.fitant[set->ray.castarc] * (set->ray.horizontalgrid - set->pattr.fpy);
			set->ray.xinter = set->ray.xtemp + set->pattr.fpx;
			set->ray.horizontalgrid--;
		}
		if (set->ray.castarc == set->ray.angle0 || set->ray.castarc == set->ray.angle180)
			set->ray.ditohorgrbehit = __FLT_MAX__;
		else
		{
			set->ray.ditonexinter = set->tabs.fxstept[set->ray.castarc];
			while (1)
			{
				set->ray.x_grid_index = (int)(set->ray.xinter / set->ray.tile_size);
				set->ray.y_grid_index = (set->ray.horizontalgrid / set->ray.tile_size);
				if ((set->ray.x_grid_index>=set->tabs.map_w) ||
					(set->ray.y_grid_index>=set->tabs.map_h) ||
					set->ray.x_grid_index<0 || set->ray.y_grid_index<0)
				{
					set->ray.ditohorgrbehit = __FLT_MAX__;
					break;
				}
				if ((set->scene.map[set->ray.y_grid_index][set->ray.x_grid_index]) == '2')
				{
					int i;

					i = 0;
					while (i < set->scene.sprnum)
					{
						if (set->sprite[i].x / 64 == set->ray.x_grid_index &&
						set->sprite[i].y / 64 == set->ray.y_grid_index)
						{
							set->sprite[i].is_visible = 1;
							// break;
							// exit (1);
						}
						i++;
					}
				}
				if ((set->scene.map[set->ray.y_grid_index][set->ray.x_grid_index]) == '1')
				{
					set->ray.ditohorgrbehit  = (set->ray.xinter-set->pattr.fpx)*set->tabs.ficost[set->ray.castarc];
					break;
				}
				else
				{
					set->ray.xinter += set->ray.ditonexinter;
					set->ray.horizontalgrid += set->ray.ditonehorg;
				}
			}
		}
		if (set->ray.castarc < set->ray.angle90 || set->ray.castarc > set->ray.angle270)
		{
			set->ray.verticalgrid  = set->ray.tile_size + (set->pattr.fpx / set->ray.tile_size) * set->ray.tile_size;
			set->ray.ditoneverg = set->ray.tile_size;

			set->ray.ytemp = set->tabs.ftant[set->ray.castarc] * (set->ray.verticalgrid  - set->pattr.fpx);
			set->ray.yinter = set->ray.ytemp + set->pattr.fpy;
		}
		else
		{
			set->ray.verticalgrid  = (set->pattr.fpx / set->ray.tile_size) * set->ray.tile_size;
			set->ray.ditoneverg = -set->ray.tile_size;

			set->ray.ytemp = set->tabs.ftant[set->ray.castarc] * (set->ray.verticalgrid  - set->pattr.fpx);
			set->ray.yinter = set->ray.ytemp + set->pattr.fpy;

			set->ray.verticalgrid--;
		}
		if (set->ray.castarc == set->ray.angle90 || set->ray.castarc == set->ray.angle270)
			set->ray.ditovergrbehit = __FLT_MAX__;
		else
		{
			set->ray.ditoneyinter = set->tabs.fystept[set->ray.castarc];
			while (1)
			{
				set->ray.x_grid_index = (set->ray.verticalgrid  / set->ray.tile_size);
				set->ray.y_grid_index = (int)(set->ray.yinter / set->ray.tile_size);

				if ((set->ray.x_grid_index>=set->tabs.map_w) ||
					(set->ray.y_grid_index>=set->tabs.map_h) ||
					set->ray.x_grid_index<0 || set->ray.y_grid_index<0)
				{
					set->ray.ditovergrbehit = __FLT_MAX__;
					break;
				}
				if ((set->scene.map[set->ray.y_grid_index][set->ray.x_grid_index]) == '2')
				{
					int i;

					i = 0;
					while (i < set->scene.sprnum)
					{
						if (set->sprite[i].x / 64 == set->ray.x_grid_index &&
						set->sprite[i].y / 64 == set->ray.y_grid_index)
						{
							set->sprite[i].is_visible = 1;
							// break;	
						}
						i++;
					}
				}
				if ((set->scene.map[set->ray.y_grid_index][set->ray.x_grid_index]) == '1')
				{
					set->ray.ditovergrbehit = (set->ray.yinter-set->pattr.fpy)*set->tabs.fisint[set->ray.castarc];
					break;
				}
				else
				{
					set->ray.yinter += set->ray.ditoneyinter;
					set->ray.verticalgrid  += set->ray.ditoneverg;
				}
			}
		}
		if (set->ray.ditohorgrbehit < set->ray.ditovergrbehit)
		{
			set->ray.dist=set->ray.ditohorgrbehit;
			rect.xoffset = (int)set->ray.xinter % set->ray.tile_size;
			rect.side = 0;
		}
		else
		{
			set->ray.dist=set->ray.ditovergrbehit;
			rect.xoffset = (int)set->ray.yinter % set->ray.tile_size;
			rect.side = 1;
		}
		if (rect.side == 0)
		{
			if (set->ray.ditonehorg > 0)
				rect.tnum = 1;
			else
				rect.tnum = 3;
		}
		else
		{
			if (set->ray.ditoneverg > 0)
				rect.tnum = 2;
			else
				rect.tnum = 0;
		}
		set->ray.dist /= set->tabs.ffisht[set->ray.castcolumn];
		set->ray.projwhei=(int)(set->ray.wall_height * (float)set->pattr.fpdtopp/set->ray.dist);
		if (set->ray.ppw / 2 == set->ray.castcolumn)
			set->ray.forhook = set->ray.projwhei;
		set->ray.bottomOfWall = set->pattr.fppycen+(int)(set->ray.projwhei*0.5F);
		set->ray.topOfWall = set->pattr.fppycen - (int)(set->ray.projwhei*0.5F);
		if (set->ray.bottomOfWall>=set->ray.pph)
				set->ray.bottomOfWall=set->ray.pph-1;
		if (set->ray.topOfWall < 0 || set->ray.topOfWall >= set->ray.ppw)
			set->ray.topOfWall = 0;
		rect.ty_step = 64.0 / (float)set->ray.projwhei;
		rect.ty_off = 0;
		if (set->ray.projwhei > set->ray.pph)
		{
			rect.ty_off = (set->ray.projwhei - set->ray.pph) / 2.0;
			set->ray.projwhei = set->ray.pph;
		}
		rect.h = set->ray.projwhei-1;
		// printf("%d - %d\n", set->scene.rxy[0], set->scene.rxy[1]);
		rect.h = abs(rect.h);
		rect.w = 1;
		rect.x = abs(set->ray.castcolumn);
		rect.y = abs(set->ray.topOfWall);
		rect.ty = fabs(rect.ty_off * rect.ty_step);
		rect.tx = abs(rect.xoffset);
		// printf("%d|%d|%d|%d|%f|%f\n", rect.h, rect.w, rect.x, rect.y, rect.ty, rect.tx);
		check_tex_rect(&rect, set);
		// printf("%d|%d|%d|%d|%f|%f\n", rect.h, rect.w, rect.x, rect.y, rect.ty, rect.tx);
		filltexrect(set, rect);
		set->ray.castarc += 1;
		if (set->ray.castarc >= set->ray.angle360)
			set->ray.castarc-= set->ray.angle360;
	}
	// exit(1);
}		
