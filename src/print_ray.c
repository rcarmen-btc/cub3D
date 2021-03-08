#include "main.h"

float arcToRad(float arcAngle)
{
     return ((float)(arcAngle * PI)/(float)ANGLE180);    
}

void			print_ray(t_set *set)
{
	int verticalGrid;        // horizotal or vertical coordinate of intersection
	int horizontalGrid;      // theoritically, this will be multiple of TILE_SIZE
							// , but some trick did here might cause
							// the values off by 1
	int distToNextVerticalGrid; // how far to the next bound (this is multiple of
	int distToNextHorizontalGrid; // tile size)
	float xIntersection;  // x and y intersections
	float yIntersection;
	float distToNextXIntersection;
	float distToNextYIntersection;

	int xGridIndex;        // the current cell that the ray is in
	int yGridIndex;

	float distToVerticalGridBeingHit;      // the distance of the x and y ray intersections from
	float distToHorizontalGridBeingHit;      // the viewpoint

	int castArc, castColumn;

	castArc = set->pattr.fpa;
		// field of view is 60 degree with the point of view (player's direction in the middle)
		// 30  30
		//    ^
		//  \ | /
		//   \|/
		//    v
		// we will trace the rays starting from the leftmost ray
	castArc-=ANGLE30;
		// wrap around if necessary
	if (castArc < 0)
	{
		castArc+=ANGLE360;
	}
	// printf("%d\n", castArc);
	// exit(1);
	for (castColumn=0; castColumn<PROJECTIONPLANEWIDTH-5; castColumn+=5)
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
		// LOOK FOR HORIZONTAL WALL
		if (castArc==ANGLE0 || castArc==ANGLE180)
		{
			distToHorizontalGridBeingHit = __FLT_MAX__;//Float.MAX_VALUE;
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
		// FOLLOW X RAY
		if (castArc < ANGLE90 || castArc > ANGLE270)
		{
			verticalGrid = TILE_SIZE + (set->pattr.fpx/TILE_SIZE)*TILE_SIZE;
			distToNextVerticalGrid = TILE_SIZE;

			float ytemp = set->tabs.ftant[castArc]*(verticalGrid - set->pattr.fpx);
			yIntersection = ytemp + set->pattr.fpy;
		}
		// RAY FACING LEFT
		else
		{
			verticalGrid = (set->pattr.fpx/TILE_SIZE)*TILE_SIZE;
			distToNextVerticalGrid = -TILE_SIZE;

			float ytemp = set->tabs.ftant[castArc]*(verticalGrid - set->pattr.fpx);
			yIntersection = ytemp + set->pattr.fpy;

			verticalGrid--;
		}

		    // LOOK FOR VERTICAL WALL
		if (castArc==ANGLE90||castArc==ANGLE270)
		{
			distToVerticalGridBeingHit = __FLT_MAX__;//Float.MAX_VALUE;
		}
		else
		{
			distToNextYIntersection = set->tabs.fystept[castArc];
			while (1)
			{
				// compute current map position to inspect
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



		// DRAW THE WALL SLICE
		// float scaleFactor;
		float dist;
		int topOfWall = 0;   // used to compute the top and bottom of the sliver that
		int bottomOfWall = 0;   // will be the staring point of floor and ceiling
		// determine which ray strikes a closer wall.
		// if yray distance to the wall is closer, the yDistance will be shorter than
			// the xDistance
		if (distToHorizontalGridBeingHit < distToVerticalGridBeingHit)
		{
				// the next function call (drawRayOnMap()) is not a part of raycating rendering part, 
				// it just draws the ray on the overhead map to illustrate the raycasting process
			// drawRayOnOverheadMap(xIntersection, horizontalGrid);
			dist=distToHorizontalGridBeingHit;
			// fOffscreenGraphics.setColor(Color.gray);
		}
		// else, we use xray instead (meaning the vertical wall is closer than
		//   the horizontal wall)
		else
		{
				// the next function call (drawRayOnMap()) is not a part of raycating rendering part, 
				// it just draws the ray on the overhead map to illustrate the raycasting process
			// drawRayOnOverheadMap(verticalGrid, yIntersection);
			dist=distToVerticalGridBeingHit;
			// fOffscreenGraphics.setColor(Color.darkGray);
		}
			// correct distance (compensate for the fishbown effect)
		dist /= set->tabs.ffisht[castColumn];
			// projected_wall_height/wall_height = fPlayerDistToProjectionPlane/dist;
		int projectedWallHeight=(int)(WALL_HEIGHT*(float)set->pattr.fpdtopp/dist);
		bottomOfWall = set->pattr.fppycen+(int)(projectedWallHeight*0.5F);
		topOfWall = PROJECTIONPLANEHEIGHT - bottomOfWall;
		if (bottomOfWall>=PROJECTIONPLANEHEIGHT)
				bottomOfWall=PROJECTIONPLANEHEIGHT-1;
		// fOffscreenGraphics.drawLine(castColumn, topOfWall, castColumn, bottomOfWall);
		// fOffscreenGraphics.fillRect(castColumn, topOfWall, 5, projectedWallHeight);
		// if (castColumn == 0 || castColumn == 5)
		// {
		// printf("verticalGrid: %d \n", verticalGrid);
		// printf("horizontalGrid: %d \n", horizontalGrid);
		// printf("distToNextVerticalGrid: %d\n", distToNextVerticalGrid);
		// printf("distToNextHorizontalGrid: %d\n", distToNextHorizontalGrid);
		// printf("xIntersection: %f\n",  xIntersection);
		// printf("yIntersection: %f\n", yIntersection);
		// printf("distToNextXIntersection: %f\n", distToNextXIntersection);
		// printf("distToNextYIntersection: %f\n", distToNextYIntersection);
		// printf("xGridIndex: %d\n", xGridIndex);
		// printf("yGridIndex: %d\n", yGridIndex);
		// printf("distToVerticalGridBeingHit: %f\n", distToVerticalGridBeingHit);
		// printf("distToHorizontalGridBeingHit: %f\n", distToHorizontalGridBeingHit);
		// printf("castArc: %d\n", castArc);
		// printf("castColumn: %d\n", castColumn);
		// printf("dist: %f\n", dist);
		// printf("topOfWall: %d\n", topOfWall);
		// printf("bottomOfWall: %d\n", bottomOfWall);
		// printf("projectedWallHeight: %d\n", projectedWallHeight);
		// printf("set->pattr.fpdtopp: %d\n ", set->pattr.fpdtopp);
		// printf("=====\n");

		// }
		// printf("verticalGrid: %d \n", verticalGrid);
		// printf("horizontalGrid: %d \n", horizontalGrid);
		// printf("distToNextVerticalGrid: %d\n", distToNextVerticalGrid);
		// printf("distToNextHorizontalGrid: %d\n", distToNextHorizontalGrid);
		// printf("xIntersection: %f\n",  xIntersection);
		// printf("yIntersection: %f\n", yIntersection);
		// printf("distToNextXIntersection: %f\n", distToNextXIntersection);
		// printf("distToNextYIntersection: %f\n", distToNextYIntersection);
		// printf("xGridIndex: %d\n", xGridIndex);
		// printf("yGridIndex: %d\n", yGridIndex);
		// printf("distToVerticalGridBeingHit: %f\n", distToVerticalGridBeingHit);
		// printf("distToHorizontalGridBeingHit: %f\n", distToHorizontalGridBeingHit);
		// printf("castArc: %d\n", castArc);
		// printf("castColumn: %d\n", castColumn);
		// printf("dist: %f\n", dist);
		// printf("topOfWall: %d\n", topOfWall);
		// printf("bottomOfWall: %d\n", bottomOfWall);
		// printf("projectedWallHeight: %d\n", projectedWallHeight);
		// printf("set->pattr.fpdtopp: %d\n ", set->pattr.fpdtopp);
		// printf("=====\n");
		if (topOfWall < 0 || topOfWall >= PROJECTIONPLANEHEIGHT)
			topOfWall = 0;
		if (projectedWallHeight > PROJECTIONPLANEHEIGHT)
			projectedWallHeight = PROJECTIONPLANEHEIGHT;
		print_fillrect(set, castColumn, topOfWall, projectedWallHeight);
		// exit(1);
		// TRACE THE NEXT RAY
		castArc+=5;
		if (castArc>=ANGLE360)
				castArc-=ANGLE360;
	}
}		
	// (void)distToHorizontalGridBeingHit;
	// (void)distToVerticalGridBeingHit;
	// print_square(set, xGridIndex, yGridIndex, 0x00FFFFFF);
	// // printf("%f - %f\n", distToHorizontalGridBeingHit, distToVerticalGridBeingHit);	
	// // print_line(set, xIntersection, yIntersection);
	


