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
	return x;
}

int Player::GetY()
{
	return y;
}

void Player::SetDirection(char _direction)
{
	direction = _direction;
}

char Player::GetDir() {
	return direction;
}

int Player::GetMyPlace() {
	return squareNumber;
}

void Player::ChangeMyPlace(int i) {
	squareNumber = i;
}

void Player::CapturePokemon(int a)
{
	if (a != 0)
	{
		pokeballs > 0 ?
			this->capturedPokemon += a,
			this->pokeballs--
			:
			0;
	}
}

void Player::DamagePokemon() {

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