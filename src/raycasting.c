#include "main.h"

float arcToRad(float arcAngle)
{
     return ((float)(arcAngle * PI)/(float)ANGLE180);    
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

	castArc = set->pattr.fpa;
	castArc-=ANGLE30;
	if (castArc < 0)
	{
		castArc+=ANGLE360;
	}
	for (castColumn=0; castColumn<PROJECTIONPLANEWIDTH-1; castColumn+=1)
	{
		if (castArc > ANGLE0 && castArc < ANGLE180)
		{
			horizontalGrid = (set->pattr.fpy/TILE_SIZE)*TILE_SIZE  + TILE_SIZE;
			distToNextHorizontalGrid = TILE_SIZE;
			float xtemp = set->tabs.fitant[castArc]*(horizontalGrid-set->pattr.fpy);
			xIntersection = xtemp + set->pattr.fpx;
		}
		else
		{
			horizontalGrid = (set->pattr.fpy/TILE_SIZE)*TILE_SIZE;
			distToNextHorizontalGrid = -TILE_SIZE;
			float xtemp = set->tabs.fitant[castArc]*(horizontalGrid - set->pattr.fpy);
			xIntersection = xtemp + set->pattr.fpx;
			horizontalGrid--;
		}
		if (castArc==ANGLE0 || castArc==ANGLE180)
		{
			distToHorizontalGridBeingHit = __FLT_MAX__;
		}
		else
		{
			distToNextXIntersection = set->tabs.fxstept[castArc];
			while (1)
			{
				xGridIndex = (int)(xIntersection/TILE_SIZE);
				yGridIndex = (horizontalGrid/TILE_SIZE);
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
		if (castArc < ANGLE90 || castArc > ANGLE270)
		{
			verticalGrid = TILE_SIZE + (set->pattr.fpx/TILE_SIZE)*TILE_SIZE;
			distToNextVerticalGrid = TILE_SIZE;

			float ytemp = set->tabs.ftant[castArc]*(verticalGrid - set->pattr.fpx);
			yIntersection = ytemp + set->pattr.fpy;
		}
		else
		{
			verticalGrid = (set->pattr.fpx/TILE_SIZE)*TILE_SIZE;
			distToNextVerticalGrid = -TILE_SIZE;

			float ytemp = set->tabs.ftant[castArc]*(verticalGrid - set->pattr.fpx);
			yIntersection = ytemp + set->pattr.fpy;

			verticalGrid--;
		}
		if (castArc==ANGLE90||castArc==ANGLE270)
			distToVerticalGridBeingHit = __FLT_MAX__;
		else
		{
			distToNextYIntersection = set->tabs.fystept[castArc];
			while (1)
			{
				xGridIndex = (verticalGrid/TILE_SIZE);
				yGridIndex = (int)(yIntersection/TILE_SIZE);

				if ((xGridIndex>=set->tabs.map_w) ||
					(yGridIndex>=set->tabs.map_h) ||
					xGridIndex<0 || yGridIndex<0)
				{
					distToVerticalGridBeingHit = __FLT_MAX__;
					break;
				}
				else if ((set->scene.map[yGridIndex][xGridIndex]) == '1')
				{
					distToVerticalGridBeingHit =(yIntersection-set->pattr.fpy)*set->tabs.fisint[castArc];
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
		int projectedWallHeight=(int)(WALL_HEIGHT*(float)set->pattr.fpdtopp/dist);
		bottomOfWall = set->pattr.fppycen+(int)(projectedWallHeight*0.5F);
		topOfWall = PROJECTIONPLANEHEIGHT - bottomOfWall;
		if (bottomOfWall>=PROJECTIONPLANEHEIGHT)
				bottomOfWall=PROJECTIONPLANEHEIGHT-1;
		if (topOfWall < 0 || topOfWall >= PROJECTIONPLANEHEIGHT)
			topOfWall = 0;
		if (projectedWallHeight > PROJECTIONPLANEHEIGHT)
			projectedWallHeight = PROJECTIONPLANEHEIGHT;
		print_fillrect(set, castColumn, topOfWall, projectedWallHeight);
		castArc+=1;
		if (castArc>=ANGLE360)
				castArc-=ANGLE360;
	}
}		
	


