/**
* //////  DoneMovingState.h  //////
*
* Ce fichier constient la classe d'�tat Done Moving 
*
* \author Cossec Est�ban
*
*/
#pragma once
#include "GameState.h"
class DoneMovingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneMovingState state_doneMoving;