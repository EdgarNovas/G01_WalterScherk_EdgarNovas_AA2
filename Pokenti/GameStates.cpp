#include "GameStates.h"

GameStates::GameStates() {
	currentState = CurrentGameState::Init;
}

void GameStates::ChangeCurrentState(CurrentGameState state) {

	currentState = state;
}

CurrentGameState GameStates::ReturnGameState() {
	return currentState;
}

