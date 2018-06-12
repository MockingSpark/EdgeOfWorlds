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
	/// fonction d'ajout d'un personnage sur la carte
	void addCharacter(Character * character, Position p);
	/// calcul de distance entre deux positions. Ne prend pas en compte le plan
	int dist(Position, Position);
	/// accesseur d'une tile
	Tile& tile(Position p) { return m_tileList[tileID(p)]; };
	/// fait bouger le joueur actif
	bool makeMove();
	/// fait attaquer le joueur actif avec son skill donné
	bool makeHit(int);
	/// bouge le curseur
	void moveCursor(Direction);
	/// fait changer de plan au personnage actif
	bool makeChangeSide();
	/// change la vu de plan
	void changeViewSide() ;
	/// change le joueur actif
	void nextPlayer(Character const *);
	/// change la direction du joueur actif
	void makeChangeDirection(Direction);
	/// reset de la map. Vide les personnages.
	void resetMap();

private:
	/// fonctions de gestion permettant de savoir si un joueur peut être attaqué
	bool hitable(Position& target, Position& origin, EdgeSide side);
	bool inRange(Position& p1, Position& p2, int rg, SkillRange rangeType);
	bool isTargetTeam(Character* target, Character* active, TargetTeam targetTeam);

protected:

	/// fonction de gestion retournant l'ID d'une tuile dans le vecteur en fonction de sa position
	int tileID(Position p) { return (p.y ) * m_xSize + p.x  + ((p.side == MEDIEVAL) ? 1 : 0) * (m_xSize*m_ySize); };

	/// la liste des tuiles.
	std::vector<Tile> m_tileList;
	/// pointeur vers la tuile active
	Tile * m_tileToPlay;

	// curseur
	Tile m_cursor;
	sf::Texture textCur;

	/// liste des combatants
	std::vector<std::tuple<Position, Character*>> m_fighters;

	/// taille de la map
	int m_xSize, m_ySize;

	/// structure de gestion nécessaire à l'utilisation de tmx
	struct TileSet {
		TileSet() : tmx(ASSETS_PATH) {};

		tmx::Tileset tmx;
		sf::Texture texture;
	};
	TileSet m_tileset;
	/// plan actif
	Side m_viewSide = TECH;
};

