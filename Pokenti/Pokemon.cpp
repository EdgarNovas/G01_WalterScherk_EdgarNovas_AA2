#include "Pokemon.h"


















void Pokemon::SetPlace(int newSquareNumber) {
	squareNumber = newSquareNumber;
}

int Pokemon::GetSquare() {
	return squareNumber;
}



void Pokemon::SetHealth(int newHealth) {
	health = newHealth;
}

int Pokemon::GetHealth() {
	return health;
}



void Pokemon::MinusHealth(int damage) {
	health = health - damage;
}



void Pokemon::SetPosX(int newPosX) {
	posX = newPosX;
}

void Pokemon::SetPosY(int newPosY) {
	posY = newPosY;
}

int Pokemon::GetPosX() {
	return posX;
}

int Pokemon::GetPosY() {
	return posY;
}