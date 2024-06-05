#include "Pokemon.h"
#include <iostream>

const int dificultyPokemon = 1;
const int dificultyMewtwo = 5;

Pokemon::Pokemon() {
	
	

	posX = 0;
	posY = 0;
	health = 0;
	squareNumber = 1;

	direction = 1;
	nature = rand() % 3;
	name = allNames[rand() % maxNames];

	minX = 0;
	minY = 0;
	maxX = 0;
	maxY = 0;

	turnCounter = 0;

	addedDifficulty = dificultyPokemon;
}

void Pokemon::SetPlace(int newSquareNumber) {
	squareNumber = newSquareNumber;
}

std::string Pokemon::GetName() {

	return name;
}

void Pokemon::SetMewtwoName() {
	name = "Mewtwo";
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

void Pokemon::DefineMinsAndMaxs(int width, int height) {
	
	if (squareNumber == 0)
	{
		minX = 0;
		minY = 0;
		maxX = (width / 2) - 1;
		maxY = (height / 2) - 1;
	}
	else if (squareNumber == 1)
	{
		minX = 0;
		minY = (height / 2) + 1;

		maxX = (width / 2) - 1;
		maxY = height - 1;
	}
}

void Pokemon::Move() {

	//turnCounter = turnsUntilNextMove;

	if (turnCounter == turnsUntilNextMove)
	{
		switch (nature)
		{
		case 0:
			if (posX + direction < minX || posX + direction > maxX)
				direction *= -1;

			posX += direction;
			break;

		case 1:
			if (posY + direction < minY || posY + direction > maxY)
				direction *= -1;

			posY += direction;
			break;

		case 2:
			if (posX + direction < minX || posX + direction > maxX || posY + direction < minY || posY + direction > maxY)
				direction *= -1;

			posX += direction;
			posY += direction;
			break;

		default:
			break;
		}


		turnCounter = 0;
	}
	else
		turnCounter++;
}

void Pokemon::SetTimeForNextMove(int min, int max) {

	turnsUntilNextMove = (rand() % (max - min)) + min;
}

void Pokemon::RandomizePokemon() {
	if (squareNumber <= 1)
	{
		posX = (rand() % (maxX - minX)) + minX;
		posY = (rand() % (maxY - minY)) + minY;
	}
	else {
		posX = -10;
		posY = -10;
	}
	
}

int Pokemon::GetDifficulty() {
	return addedDifficulty;
}

void Pokemon::SetMewtwoDifficulty() {
	addedDifficulty = dificultyMewtwo;
}
void Pokemon::SetMewtwoNature() {
	nature = -1;
}


void Pokemon::IsMewtwoCaptured(bool& hasMewTwo) {
	if (nature == -1) {
		hasMewTwo = true;
	}

}