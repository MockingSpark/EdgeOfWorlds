/**
* //////  EndOfTurnState.h  //////
*
* Ce fichier constient la classe d'�tat EndOfTurn
*
* \author Cossec Est�ban
*
*/
#pragma once
#include "GameState.h"
class EndOfTurnState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};


static EndOfTurnState state_endOfTurn;