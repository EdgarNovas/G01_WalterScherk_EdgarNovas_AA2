#pragma once
class GameStates
{
private:
	enum class CurrentGameState
	{
		Init,Menu,Game,GameOver
	};

	CurrentGameState currentState;

	GameStates() {
		currentState = CurrentGameState::Init;
	}

public:

	void ChangeCurrentState(CurrentGameState state) {
		currentState = state;
	}
};

