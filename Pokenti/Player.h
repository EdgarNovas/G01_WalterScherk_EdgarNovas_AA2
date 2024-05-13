#pragma once
class Player
{
private:
	int x = 0;
	int y = 0;
	char direction = '>';
	int capturedPokemon = 0;

public:
	void SetPosition(int _x, int _y);

	int GetX();
	
	int GetY();

	void SetDirection(char direction);

	char GetDir();

	void CapturePokemon(int a);

	int ShowCapturedPokemon();


};

