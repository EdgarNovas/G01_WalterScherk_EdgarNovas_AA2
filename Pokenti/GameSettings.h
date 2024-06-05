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

    int pokemonAround1;
    int pokemonNeeded1;
    int pokemonAround2;
    int pokemonNeeded2;

    bool fighting;
    bool hasMewtwo;
    bool gameOver;


    GameSettings();
};

