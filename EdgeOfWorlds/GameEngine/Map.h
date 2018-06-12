/**
* //////  Map.h  //////
*
* Ce fichier constient la classe Map, gérant la carte et ses interactions avec les Personnages
*
* \author Cossec Estéban
*
*/

#pragma once

#include <vector>
#include "Character.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SFML/Graphics.hpp>

#define ASSETS_PATH "..\\Assets\\maps\\tileset.tsx"

/**
  * \class Map
  *
  * Cette classe gère la carte de jeu. Cette carte est une carte isométrique, designé par TiledMaps.
  */
class Map
{
protected:

	/// Définit une tuile, élément unitaire composant ma carte
	struct Tile {
		/// constructeur
		Tile(Position);
		/// position
		Position pos;
		/// pointeur d'observation sur un potentiel personnage
		Character* entity;
		/// sprite nécessaire à l'affichage
		sf::Sprite sprite;
	};

public:
	/// Le constructeur de la Map prend en argument le chemin vers le fichier .tmx
	Map(std::string);
	/// fonction d'affichage de la carte
	void draw(sf::RenderTarget &);
	/// 
	void addCharacter(Character * character, Position p);

	int dist(Position, Position);

	Tile& tile(Position p) { return m_tileList[tileID(p)]; };

	bool makeMove();

	bool makeHit(int);

	void moveCursor(Direction);

	bool makeChangeSide();

	void changeViewSide() ;

	void nextPlayer(Character const *);

	void makeChangeDirection(Direction);

	void resetMap();

private:
	bool hitable(Position& target, Position& origin, EdgeSide side);
	bool inRange(Position& p1, Position& p2, int rg, SkillRange rangeType);
	bool isTargetTeam(Character* target, Character* active, TargetTeam targetTeam);

protected:

	
	int tileID(Position p) { return (p.y ) * m_xSize + p.x  + ((p.side == MEDIEVAL) ? 1 : 0) * (m_xSize*m_ySize); };


	std::vector<Tile> m_tileList;

	Tile * m_tileToPlay;

	// curseur
	Tile m_cursor;
	sf::Texture textCur;

	std::vector<std::tuple<Position, Character*>> m_fighters;

	int m_xSize, m_ySize;

	struct TileSet {
		TileSet() : tmx(ASSETS_PATH) {};

		tmx::Tileset tmx;
		sf::Texture texture;
	};

	TileSet m_tileset;

	Side m_viewSide = TECH;
};

