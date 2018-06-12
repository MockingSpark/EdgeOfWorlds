/**
* //////  DoneNothingKingState.h  //////
*
* Ce fichier constient la classe d'�tat Done Nothing King
*
* \author Cossec Est�ban
*
*/
#pragma once
#include "GameState.h"
class DoneNothingKingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneNothingKingState state_doneNothingKing;