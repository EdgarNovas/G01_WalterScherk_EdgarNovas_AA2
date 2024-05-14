#pragma once
class Player
{
private:
	int x;
	int y;
	char direction;
	int capturedPokemon;
	int pokeballs;

public:
	Player();

	void SetPosition(int _x, int _y);

	int GetX();
	
	int GetY();

	void SetDirection(char direction);

	char GetDir();

	void CapturePokemon(int a);

	void IncreasePokeballs();

	int GetPokeballs();

	int ShowCapturedPokemon();


};

