#include "main.h"

float arcToRad(float arcAngle, t_set *set)
{
	return ((float)(arcAngle * PI)/(float)set->ray.angle180);    
}

void			raycasting(t_set *set)
{
	int verticalGrid;
	int horizontalGrid;
	int distToNextVerticalGrid;
	int distToNextHorizontalGrid;
	float xIntersection;
	float yIntersection;
	float distToNextXIntersection;
	float distToNextYIntersection;
	int xGridIndex;
	int yGridIndex;
	float distToVerticalGridBeingHit;
	float distToHorizontalGridBeingHit;
	int castArc, castColumn;
	float dist;
	int topOfWall = 0;
	int bottomOfWall = 0;
	t_rect rect;

	castArc = set->pattr.fpa;
	castArc -= set->ray.angle30;
	if (castArc < 0)
		castArc += set->ray.angle360;
	for (castColumn = 0; castColumn < set->ray.ppw; castColumn+=1)
	{
		if (castArc > set->ray.angle0 && castArc < set->ray.angle180)
		{
			horizontalGrid = (set->pattr.fpy / set->ray.tile_size) * set->ray.tile_size + set->ray.tile_size;
			distToNextHorizontalGrid = set->ray.tile_size;
			float xtemp = set->tabs.fitant[castArc]*(horizontalGrid - set->pattr.fpy);
			xIntersection = xtemp + set->pattr.fpx;
		}
		else
		{
			horizontalGrid = (set->pattr.fpy / set->ray.tile_size) * set->ray.tile_size;
			distToNextHorizontalGrid = -set->ray.tile_size;
			float xtemp = set->tabs.fitant[castArc] * (horizontalGrid - set->pattr.fpy);
			xIntersection = xtemp + set->pattr.fpx;
			horizontalGrid--;
		}
		if (castArc == set->ray.angle0 || castArc == set->ray.angle180)
			distToHorizontalGridBeingHit = __FLT_MAX__;
		else
		{
			distToNextXIntersection = set->tabs.fxstept[castArc];
			while (1)
			{
				xGridIndex = (int)(xIntersection / set->ray.tile_size);
				yGridIndex = (horizontalGrid / set->ray.tile_size);
				if ((xGridIndex>=set->tabs.map_w) ||
					(yGridIndex>=set->tabs.map_h) ||
					xGridIndex<0 || yGridIndex<0)
				{
					distToHorizontalGridBeingHit = __FLT_MAX__;
					break;
				}
				else if ((set->scene.map[yGridIndex][xGridIndex]) == '1')
				{
					distToHorizontalGridBeingHit  = (xIntersection-set->pattr.fpx)*set->tabs.ficost[castArc];
					break;
				}
				else
				{
					xIntersection += distToNextXIntersection;
					horizontalGrid += distToNextHorizontalGrid;
				}
			}
		}
		if (castArc < set->ray.angle90 || castArc > set->ray.angle270)
		{
			verticalGrid = set->ray.tile_size + (set->pattr.fpx / set->ray.tile_size) * set->ray.tile_size;
			distToNextVerticalGrid = set->ray.tile_size;

			float ytemp = set->tabs.ftant[castArc] * (verticalGrid - set->pattr.fpx);
			yIntersection = ytemp + set->pattr.fpy;
		}
		else
		{
			verticalGrid = (set->pattr.fpx / set->ray.tile_size) * set->ray.tile_size;
			distToNextVerticalGrid = -set->ray.tile_size;

			float ytemp = set->tabs.ftant[castArc] * (verticalGrid - set->pattr.fpx);
			yIntersection = ytemp + set->pattr.fpy;

			verticalGrid--;
		}
		if (castArc == set->ray.angle90 || castArc == set->ray.angle270)
			distToVerticalGridBeingHit = __FLT_MAX__;
		else
		{
			distToNextYIntersection = set->tabs.fystept[castArc];
			while (1)
			{
				xGridIndex = (verticalGrid / set->ray.tile_size);
				yGridIndex = (int)(yIntersection / set->ray.tile_size);

				if ((xGridIndex>=set->tabs.map_w) ||
					(yGridIndex>=set->tabs.map_h) ||
					xGridIndex<0 || yGridIndex<0)
				{
					distToVerticalGridBeingHit = __FLT_MAX__;
					break;
				}
				else if ((set->scene.map[yGridIndex][xGridIndex]) == '1')
				{
					distToVerticalGridBeingHit = (yIntersection-set->pattr.fpy)*set->tabs.fisint[castArc];
					break;
				}
				else
				{
					yIntersection += distToNextYIntersection;
					verticalGrid += distToNextVerticalGrid;
				}
			}
		}
		if (distToHorizontalGridBeingHit < distToVerticalGridBeingHit)
			dist=distToHorizontalGridBeingHit;
		else
			dist=distToVerticalGridBeingHit;
		dist /= set->tabs.ffisht[castColumn];
		int projectedWallHeight=(int)(set->ray.wall_height * (float)set->pattr.fpdtopp/dist);
		bottomOfWall = set->pattr.fppycen+(int)(projectedWallHeight*0.5F);
		topOfWall = set->ray.pph - bottomOfWall;
		if (bottomOfWall>=set->ray.pph)
				bottomOfWall=set->ray.pph-1;
		if (topOfWall < 0 || topOfWall >= set->ray.ppw)
			topOfWall = 0;
		if (projectedWallHeight > set->ray.pph)
			projectedWallHeight = set->ray.pph;
		rect.color = 0x00FF99FF;
		rect.h = projectedWallHeight;
		rect.w = 1;
		rect.x = castColumn;
		rect.y = topOfWall;
		fillrect(set, rect);
		castArc += 1;
		if (castArc >= set->ray.angle360)
				castArc-= set->ray.angle360;
	}
}		
	


