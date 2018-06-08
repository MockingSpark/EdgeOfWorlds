#pragma once

#include <vector>
#include "Character.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SFML/Graphics.hpp>

#define MOVEMENT_COUNT 3 // TODO ajouter une stat de mvt
#define ASSETS_PATH "..\\Assets\\maps\\tileset.tsx"


class Map
{
protected:

	struct Tile {

		Tile(Position&);

		Position pos;

		std::shared_ptr<Character> entity;
		sf::Sprite sprite;
	};

public:
	Map(std::string);

	void draw(sf::RenderTarget & t, Side);

	bool addCharacter(std::weak_ptr<Character> character, Position p);

	Tile& tile(Position p) { return m_tileList[(m_ySize - p.y - 1) * m_xSize + p.x]; };

protected:

	



	std::vector<Tile> m_tileList;

	Tile * m_tileToPlay;
	Tile * m_cursor;

	std::map<Position, std::shared_ptr<Character>> m_fighters;

	int m_xSize, m_ySize;

	struct TileSet {
		TileSet() : tmx(ASSETS_PATH) {};

		tmx::Tileset tmx;
		sf::Texture texture;
	};

	TileSet m_tileset;

	// TODO
};

