#include "GameSettings.h"

GameSettings::GameSettings() {
	width = 0;
	height = 0;
	pikachuDamage = 0;
	pokemonMaxHealth = 0;
	mewTwoHealht = 0;
	minWaitTurns = 0;
	maxWaitTurns = 0;

	pokemonAround1 = 0;
	pokemonNeeded1 = 0;
	pokemonAround2 = 0;
	pokemonNeeded2 = 0;

	fighting = false;
	hasMewtwo = false;
	gameOver = false;
}