#include "Player.h"


void Player::SetPosition(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
}

int Player::GetX()
{
	return this->x;
}

int Player::GetY()
{
	return this->y;
}

void Player::SetDirection(char direction)
{
	this->direction = direction;
}

char Player::GetDir() {
	return this->direction;
}

void Player::CapturePokemon()
{
	capturedPokemon++;
}
