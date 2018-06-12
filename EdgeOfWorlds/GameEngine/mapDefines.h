/**
* //////  mapDefine.h  //////
*
* Ce fichier constient les definitions n�cessaires aupositionnement sur la map
*
* \author Cossec Est�ban
*
*/
#pragma once

/// le plan
enum Side {
	MEDIEVAL = 0,
	TECH = 1,
};

/// position compl�te, prenant en compte le plan
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