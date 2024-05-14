#include "Player.h"


Player::Player() {
	this->x = 0;
	this->y = 0;
	this->direction = '>';
	this->capturedPokemon = 0;
	this->pokeballs = 0;
}

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

void Player::CapturePokemon(int a)
{
	this->capturedPokemon += a;
	this->pokeballs--;
}

void Player::IncreasePokeballs() {
	this->pokeballs++;
}

int Player::GetPokeballs() {
	return this->pokeballs;
}

int Player::ShowCapturedPokemon() {
	return this->capturedPokemon;
}