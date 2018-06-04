#include "stdafx.h"
#include "Map.h"


Tile& Map::operator()(size_t i, size_t j)
{
	return m_map[i * m_cols + j];
}