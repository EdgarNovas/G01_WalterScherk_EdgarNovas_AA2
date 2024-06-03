#include "Player.h"


Player::Player() {
	x = 0;
	y = 0;
	direction = '>';
	capturedPokemon = 0;
	pokeballs = 10;

	//hasMewtwo = false;
}

void Player::SetPosition(int _x, int _y) {
	x = _x;
	y = _y;
}

int Player::GetX() {
	return x;
}

int Player::GetY() {
	return y;
}

void Player::SetDirection(char _direction) {
	direction = _direction;
}

bool Player::IsInLeague(int width, int height) {
	if (y < width/2)
	{
		if (x > height / 2)
		{
			return true;
		}
	}
	return false;
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

void Player::CapturePokemon() {
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