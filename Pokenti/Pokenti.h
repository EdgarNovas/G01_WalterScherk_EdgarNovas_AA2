#pragma once

struct Pokeball {
    int posX = 2;
    int posY = 2;

    int square = 0;
};


void CleanKeys();
bool PutPokemon(Pokemon* pokemons, int allPokemonAround, int& posX, int& posY);
bool PutPokeball(Pokeball* pokeballs, int& allPokeballAround, int& posX, int& posY);
void RandomizePokeball(Pokeball& pokeball, int maxPokeballs, int index, int width, int height);
void CheckNumbers(std::string linea, int& leftNum, int& rightNum, bool& leftNumber);
void CheckOneNumber(std::string linea, int& num);
bool CheckIfPokemonIsCapturable(Pokemon& pokemon, int maxHealth, int& width, int& height, bool& fighting);
void DamagePokemon(Pokemon& pokemon, bool& fighting, int damage, int maxHealth);
void ShowCombatOptions(Pokemon& pokemon);
void FunctionThatStartsCombat(Pokemon* pokemons, int allPokemons, Player me, bool& fighting, int& currentPokemonNum);



