#pragma once

#include <vector>
#include "Character.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SFML/Graphics.hpp>

class Map
{

public:
	Map(std::string);

	void draw(sf::RenderTarget & t);

protected:
	
	enum Side {
		TECH,
		MEDIEVAL,
	};

	struct Tile {
		Position pos;
		std::shared_ptr<Character> entity;
		std::shared_ptr<sf::Sprite> sprite;
	};

	struct Position {
		int x;
		int y;
		Side side;
	};

	tmx::Map m_map;

	std::vector<Tile> m_techSide;
	std::vector<Tile> m_medievalSide;

	Tile * m_activeTile;
	// TODO
};

