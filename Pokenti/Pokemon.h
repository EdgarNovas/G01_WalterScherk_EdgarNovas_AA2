#pragma once
class Pokemon
{
    int posX;
    int posY;
    int health;
    int squareNumber;

public:
    
    int GetPosX();
    int GetPosY();
    void SetPosX(int newPosX);
    void SetPosY(int newPosY);

    void SetPlace(int newSquareNumber);
    int GetSquare();

    void SetHealth(int newHealth);
    int GetHealth();

    void MinusHealth(int damage);
};

