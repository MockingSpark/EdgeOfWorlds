/**
* //////  DoneNothingKingState.h  //////
*
* Ce fichier constient la classe d'état Done Nothing King
*
* \author Cossec Estéban
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