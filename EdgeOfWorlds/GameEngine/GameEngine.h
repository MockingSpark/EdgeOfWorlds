/**
* //////  GameEngine.h  //////
*
* Ce fichier constient la classe d'entrée de la librairie. C'est la seule inclusion nécessaire dans le projet d'entrée.
*
* \author Cossec Estéban
*
*/
#pragma once

#include "Character.h"
#include "Map.h"
#include "mapDefines.h"
#include "PersoDefines.h"
#include "Skill.h"
#include "skillDefine.h"
#include "Elements.h"
#include "GameState.h"
#include "IdCard.h"
#include "Helper.h"

/**
* \class GameEngine
*
* Il s'agit de la classe de gestion générale du jeu.
*/
class GameEngine final
{
public:

	GameEngine();

	/// mrthode à appeler pour lancer le jeu
	int run(); 
	/// accesseur de la map
	Map& getMap() { return m_map; };
	/// changer de state de jeu
	void changeState(GameState*);
	/// met fin au tour
	void endOfTurn(); //< Update the state 
	/// initialisation de la partie
	void initialise();
	/// fin de la partie
	void gameOver() { initialise(); };
	/// met à jour la GUI d'aide
	void updateHelper(bool move = true, bool change = true, bool attack = true) { m_helper.update(move, change, attack); };

private:
	/// fonction interne servant à savoir si la partie est finie
	bool isOver();

private:

	Map m_map;
	sf::RenderTexture m_mapTexture;
	sf::Sprite m_mapSprite;
	sf::RenderWindow m_window;

	GameState* m_state; //< Predicate : is ptr on static object so it is OK

	std::vector<std::unique_ptr<Character>> m_redPlayers;
	std::vector<std::unique_ptr<Character>> m_bluePlayers;

	int m_blueIterator = 0;
	int m_redIterator = 0;

	int m_blueKing = 0;
	int m_redKing = 0;

	Character::Team m_currentTeam;

	//cards
	std::vector<std::unique_ptr<IdCard>> m_cards;


	Helper m_helper;


};
