/**
* //////  GameState.h  //////
*
* Ce fichier contient la classe m�re des �tats.
*
* La machine � �tat utilis�e est d�crite par diagramme en anexe.
*
* J'utilise ici une machine � �tats pour g�rer le d�roulement d'un tour. Lors d'un tour, un joueur � le droit �
*  - Deux actions Diff�rentes (attaquer est une action, quelle que soit l'attaque)
*  - Si ce n'est pas le roi, il a le droit de changer de plan. Le roi nepeut pas.
*
* \author Cossec Est�ban
*
*/
#pragma once

#include "Map.h"
#include "Character.h"

class GameEngine;

class GameState
{
public:
	


public:
	virtual bool handleInput(GameEngine&, sf::Event&) = 0; //< \return true if the window has to be closed

protected:
};

