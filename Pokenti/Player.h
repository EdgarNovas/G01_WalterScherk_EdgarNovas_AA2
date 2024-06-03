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

	//bool hasMewtwo;
public:
	Player();

	void SetPosition(int _x, int _y);

	int GetX();
	
	int GetY();

	void SetDirection(char _direction);

	bool IsInLeague(int width, int height);

	char GetDir();

	int GetMyPlace();
	void ChangeMyPlace(int i);

	void CapturePokemon();

	void IncreasePokeballs();
	void DecreasePokeballs();
	int GetPokeballs();

	int ShowCapturedPokemon();

	void DamagePokemon();


};

