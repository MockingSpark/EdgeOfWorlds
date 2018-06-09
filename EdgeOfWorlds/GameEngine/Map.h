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

		Tile(Position);

		Position pos;

		std::shared_ptr<Character> entity;
		sf::Sprite sprite;
	};

public:
	Map(std::string);

	void draw(sf::RenderTarget &);

	void addCharacter(Character* character, Position p);

	int dist(Position, Position);

	Tile& tile(Position p) { return m_tileList[tileID(p)]; };

	bool makeMove();

	bool makeHit();

	void moveCursor(Direction);

	void makeChangeSide();

	void changeViewSide() ;

	void nextPlayer(Character*);

protected:

	
	int tileID(Position p) { return (p.y ) * m_xSize + p.x  + ((p.side == MEDIEVAL) ? 1 : 0) * (m_xSize*m_ySize); };


	std::vector<Tile> m_tileList;

	Tile * m_tileToPlay;

	// curseur
	Tile m_cursor;
	sf::Texture textCur;

	std::vector<std::tuple<Position, std::shared_ptr<Character>>> m_fighters;

	int m_xSize, m_ySize;

	struct TileSet {
		TileSet() : tmx(ASSETS_PATH) {};

		tmx::Tileset tmx;
		sf::Texture texture;
	};

	TileSet m_tileset;

	Side m_viewSide = TECH;
};

