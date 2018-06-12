/**
* //////  DoneNothingState.h  //////
*
* Ce fichier constient la classe d'�tat Done Nothing
*
* \author Cossec Est�ban
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