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

	GameStates() {
		currentState = CurrentGameState::Init;
	}

	void ChangeCurrentState(CurrentGameState state) {

		currentState = state;
	}

	CurrentGameState ReturnGameState() {
		return currentState;
	}

};

