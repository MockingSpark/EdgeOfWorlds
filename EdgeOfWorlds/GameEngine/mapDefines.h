#pragma once

enum Side {
	MEDIEVAL = 0,
	TECH = 1,
};

struct Position {
	int x;
	int y;
	Side side;
};

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};