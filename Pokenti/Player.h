#pragma once
class Player
{
private:
	int x;
	int y;
	char direction;
	int capturedPokemon;
	int pokeballs;

	int squareNumber;

public:
	Player();

	void SetPosition(int _x, int _y);

	int GetX();
	
	int GetY();

	void SetDirection(char _direction);

	char GetDir();

	int GetMyPlace();
	void ChangeMyPlace(int i);

	void CapturePokemon(int a);

	void IncreasePokeballs();

	int GetPokeballs();

	int ShowCapturedPokemon();

	void DamagePokemon();


};

