/**
* //////  mapDefine.h  //////
*
* Ce fichier constient les definitions nécessaires aupositionnement sur la map
*
* \author Cossec Estéban
*
*/
#pragma once

/// le plan
enum Side {
	MEDIEVAL = 0,
	TECH = 1,
};

/// position complète, prenant en compte le plan
struct Position {
	int x;
	int y;
	Side side;
};

/// direction 
enum Direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};