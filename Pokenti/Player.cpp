#include "Player.h"


Player::Player() {
	x = 10;
	y = 10;
	direction = '>';
	capturedPokemon = 0;
	pokeballs = 0;
}

void Player::SetPosition(int _x, int _y)
{
	x = _x;
	y = _y;
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

void Player::CapturePokemon()
{
	pokeballs > 0 ?
		capturedPokemon++,
		pokeballs--
		:
		0;
}

void Player::DamagePokemon() {

}

void Player::IncreasePokeballs() {
	pokeballs++;
}

void Player::DecreasePokeballs()
{
	if (pokeballs > 0)
		pokeballs--;
}

int Player::GetPokeballs() {
	return pokeballs;
}

int Player::ShowCapturedPokemon() {
	return capturedPokemon;
}