/**
* //////  DoneMovingKingState.h  //////
*
* Ce fichier constient la classe d'�tat Done Moving King
*
* \author Cossec Est�ban
*
*/
#pragma once
#include "GameState.h"
class DoneMovingKingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneMovingKingState state_doneMovingKing;