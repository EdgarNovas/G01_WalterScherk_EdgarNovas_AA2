#pragma once
class GameSettings
{
    

public:
    int width;
    int height;
    int pikachuDamage;
    int pokemonMaxHealth;
    int mewTwoHealht;
    int minWaitTurns;
    int maxWaitTurns;
    int currentPokemonIndex;
    int maxPokeballs;

    int pokemonAround1;
    int pokemonNeeded1;
    int pokemonAround2;
    int pokemonNeeded2;
    int allPokemonAround;

    int lowerX;
    int higherX;
    int lowerY;
    int higherY;

    bool fighting;
    bool hasMewtwo;
    bool gameOver;


    GameSettings();
};

