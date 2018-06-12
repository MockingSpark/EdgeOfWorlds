/**
* //////  GameState.h  //////
*
* Ce fichier contient la classe mère des états.
*
* La machine à état utilisée est décrite par diagramme en anexe.
*
* J'utilise ici une machine à états pour gérer le déroulement d'un tour. Lors d'un tour, un joueur à le droit à
*  - Deux actions Différentes (attaquer est une action, quelle que soit l'attaque)
*  - Si ce n'est pas le roi, il a le droit de changer de plan. Le roi nepeut pas.
*
* \author Cossec Estéban
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

