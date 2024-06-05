#pragma once

enum class CurrentGameState
{
	Init, Menu, Game, GameOver
};




class GameStates
{
private:
	
	CurrentGameState currentState;
public:

	GameStates();

	void ChangeCurrentState(CurrentGameState state);

	CurrentGameState ReturnGameState();

};

