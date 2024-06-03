#pragma once
class Pokemon
{
    int posX;
    int posY;
    int health;
    int squareNumber;

    int direction;
    int nature;
    int turnsUntilNextMove;
    int turnCounter;

    int minX;
    int minY;
    int maxX;
    int maxY;

    int addedDifficulty;
public:
    
    Pokemon();

    int GetPosX();
    int GetPosY();
    void SetPosX(int newPosX);
    void SetPosY(int newPosY);

    void RandomizePokemon();

    void DefineMinsAndMaxs(int width, int height);
    void Move();
    void SetTimeForNextMove(int min, int max);

    void SetPlace(int newSquareNumber);
    int GetSquare();

    void SetHealth(int newHealth);
    int GetHealth();

    void MinusHealth(int damage);

    int GetDifficulty();
    void SetMewtwoDifficulty();
    void SetMewtwoNature();
};

