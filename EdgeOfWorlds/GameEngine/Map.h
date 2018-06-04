#pragma once

#include <vector>
#include "Character.h"

class Tile
{
protected:
	Character* m_perso;
	//sf::Sprite m_sprite;
};

class Map
{
public:


	Tile & operator()(size_t i, size_t j);
	void MakeAttack(Character const*, int);

protected:
	size_t m_rows;
	size_t m_cols;
	std::vector<Tile> m_map;

};

