#include "main.h"

float arcToRad(float arcAngle, t_set *set)
{
	return ((float)(arcAngle * PI)/(float)set->ray.angle180);    
}

void			raycasting(t_set *set)
{
	int projectedWallHeight;
	int	xoffset;
	int topOfWall = 0;
	int bottomOfWall = 0;
	t_rect rect;

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
			float xtemp = set->tabs.fitant[set->ray.castarc]*(set->ray.horizontalgrid - set->pattr.fpy);
			set->ray.xinter = xtemp + set->pattr.fpx;
		}
		else
		{
			set->ray.horizontalgrid = (set->pattr.fpy / set->ray.tile_size) * set->ray.tile_size;
			set->ray.ditonehorg = -set->ray.tile_size;
			float xtemp = set->tabs.fitant[set->ray.castarc] * (set->ray.horizontalgrid - set->pattr.fpy);
			set->ray.xinter = xtemp + set->pattr.fpx;
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
				// printf("%d - %d\n", set->ray.x_grid_index, set->ray.y_grid_index);
				if ((set->ray.x_grid_index>=set->tabs.map_w) ||
					(set->ray.y_grid_index>=set->tabs.map_h) ||
					set->ray.x_grid_index<0 || set->ray.y_grid_index<0)
				{
					set->ray.ditohorgrbehit = __FLT_MAX__;
					break;
				}
				else if ((set->scene.map[set->ray.y_grid_index][set->ray.x_grid_index]) == '1')
				{
					set->ray.ditohorgrbehit  = (set->ray.xinter-set->pattr.fpx)*set->tabs.ficost[set->ray.castarc];
					break;
				}
				else
				{
					set->ray.xinter += set->ray.ditonexinter;
					set->ray.horizontalgrid += set->ray.ditonehorg;

					// printf("%d\n", set->ray.ditonehorg);
				}
			}
		}
		if (set->ray.castarc < set->ray.angle90 || set->ray.castarc > set->ray.angle270)
		{
			set->ray.verticalgrid  = set->ray.tile_size + (set->pattr.fpx / set->ray.tile_size) * set->ray.tile_size;
			set->ray.ditoneverg = set->ray.tile_size;

			float ytemp = set->tabs.ftant[set->ray.castarc] * (set->ray.verticalgrid  - set->pattr.fpx);
			set->ray.yinter = ytemp + set->pattr.fpy;
		}
		else
		{
			set->ray.verticalgrid  = (set->pattr.fpx / set->ray.tile_size) * set->ray.tile_size;
			set->ray.ditoneverg = -set->ray.tile_size;

			float ytemp = set->tabs.ftant[set->ray.castarc] * (set->ray.verticalgrid  - set->pattr.fpx);
			set->ray.yinter = ytemp + set->pattr.fpy;

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
				else if ((set->scene.map[set->ray.y_grid_index][set->ray.x_grid_index]) == '1')
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
		// int raydirx;
		// int raydiry;
		// int side;
		if (set->ray.ditohorgrbehit < set->ray.ditovergrbehit)
		{
			set->ray.dist=set->ray.ditohorgrbehit;
			xoffset = (int)set->ray.xinter % set->ray.tile_size;
			rect.side = 0;
		}
		else
		{
			set->ray.dist=set->ray.ditovergrbehit;
			xoffset = (int)set->ray.yinter % set->ray.tile_size;
			rect.side = 1;
		}
		if (rect.side == 0)
		{
			if (set->ray.ditonehorg > 0)
				rect.tnum = 3;
			else
				rect.tnum = 1;
		}
		else
		{
			if (set->ray.ditoneverg > 0)
				rect.tnum = 0;
			else
				rect.tnum = 2;
		}
		set->ray.dist /= set->tabs.ffisht[set->ray.castcolumn];
		projectedWallHeight=(int)(set->ray.wall_height * (float)set->pattr.fpdtopp/set->ray.dist);
		bottomOfWall = set->pattr.fppycen+(int)(projectedWallHeight*0.5F);
		topOfWall = set->pattr.fppycen - (int)(projectedWallHeight*0.5F);
		if (bottomOfWall>=set->ray.pph)
				bottomOfWall=set->ray.pph-1;
		if (topOfWall < 0 || topOfWall >= set->ray.ppw)
			topOfWall = 0;
		rect.ty_step = 64.0 / (float)projectedWallHeight;
		rect.ty_off = 0;
		if (projectedWallHeight > set->ray.pph)
		{
			rect.ty_off = (projectedWallHeight - set->ray.pph) / 2.0;
			projectedWallHeight = set->ray.pph;
		}
		rect.h = projectedWallHeight;//(bottomOfWall-topOfWall) - 1;
		rect.w = 1;
		rect.x = set->ray.castcolumn;
		rect.y = topOfWall;
		rect.ty = rect.ty_off * rect.ty_step;
		rect.tx = xoffset;
		// printf("%d - %d - %d - %d\n", rect.h, rect.w, rect.x, rect.y);
		filltexrect(set, rect);
		set->ray.castarc += 1;
		if (set->ray.castarc >= set->ray.angle360)
				set->ray.castarc-= set->ray.angle360;
	}
}		
