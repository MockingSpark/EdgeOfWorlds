/**
* //////  DoneNothingState.h  //////
*
* Ce fichier constient la classe d'état Done Nothing
*
* \author Cossec Estéban
*
*/
#pragma once
#include "GameState.h"
class DoneNothingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};


static DoneNothingState state_doneNothing;