#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "Player.h"
#include "GameStates.h"
#include "Pokemon.h"

const int MAX_MAP = 3;
const int CHAR_NUM_TO_NUM = 48;
const int POKE_COMBAT_AREA_MIN = -1;
const int POKE_COMBAT_AREA_MAX = 2;

const int MILLIS_FOR_NEXT_FRAME = 500;

const int SQUARE0 = 0;
const int SQUARE1 = 1;
const int SQUARE2 = 2;
const int SQUARE3 = 3;

std::ifstream archivo("config.txt");
int linesToRead = 0;

struct Pokeball {
    int posX = 2;
    int posY = 2;

    int square = 0;
};

void CleanKeys() {
    GetAsyncKeyState(VK_RIGHT);
    GetAsyncKeyState(VK_LEFT);
    GetAsyncKeyState(VK_DOWN);
    GetAsyncKeyState(VK_UP);
    GetAsyncKeyState(VK_SPACE);
    GetAsyncKeyState(VK_SHIFT);
    GetAsyncKeyState(VK_BACK);
}

bool PutPokemon(Pokemon* pokemons, int allPokemonAround, int& posX, int& posY) {
    
    for (int a = 0; a < allPokemonAround -1; a++) {


        if (pokemons[a].GetPosX() == posX && pokemons[a].GetPosY() == posY) {
                
            return true;
        }
    }

    return false;
}

void PutPokemon2(char** map, int& posX, int& posY) {

    map[posX][posY] == 'P';

}

bool PutPokeball(Pokeball* pokeballs, int& allPokeballAround, int& posX, int& posY) {

    for (int a = 0; a < allPokeballAround; a++) {


        if (pokeballs[a].posX == posX && pokeballs[a].posY == posY) {

            return true;
        }
    }

    return false;
}


void RandomizePokeball(Pokeball& pokeball, int maxPokeballs, int index, int width, int height) {

    if (index < maxPokeballs / 4) {
        pokeball.posX = rand() % ((width / 2) - 1);
        pokeball.posY = rand() % ((height / 2) - 1);
    }
    else if (index < maxPokeballs / 2) {
        pokeball.posX = rand() % ((width / 2) - 1);
        pokeball.posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1));
    }
    else if (index < (maxPokeballs / 4) * 3) {
        pokeball.posX = ((width / 2) + 1) + (rand() % ((width / 2) - 1));
        pokeball.posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1));
    }
    else {
        pokeball.posX = ((width / 2) + 1) + (rand() % ((width / 2) - 1));
        pokeball.posY = rand() % ((height / 2) - 1);
    }
}

void CheckNumbers(std::string linea, int& leftNum, int& rightNum, bool& leftNumber) {

    for (int j = 0; j < linea.size(); j++) {

        if (linea[j] != ';' && leftNumber) {
            leftNum *= 10;
            leftNum += linea[j] - CHAR_NUM_TO_NUM;
        }
        else if (leftNumber)
            leftNumber = false;
        else if (linea[j] != ';') {
            rightNum *= 10;
            rightNum += linea[j] - CHAR_NUM_TO_NUM;
        }
        else
            leftNumber = true;
    }
}

void CheckOneNumber(std::string linea, int& num) {
    for (int i = 0; i < linea.size(); i++)
    {
        if (linea[i] != ';') {
            num *= 10;
            num += linea[i] - CHAR_NUM_TO_NUM;
        }
        
    }
}

bool CheckIfPokemonIsCapturable(Pokemon& pokemon, int& width, int& height, bool& fighting) {

    
    int random = rand() % (pokemon.GetHealth() + pokemon.GetDifficulty());

    if (random <= 1)
    {
        pokemon.RandomizePokemon();

        return true;
    }

    return false;
}

void DamagePokemon(Pokemon& pokemon, int& width, int& height, bool& fighting, int damage, int maxHealth) {


    pokemon.MinusHealth(damage);
    if (pokemon.GetHealth() <= 0)
    {
        fighting = false;
        pokemon.SetHealth(maxHealth);

        pokemon.RandomizePokemon();
    }

}

void ShowCombatOptions(Pokemon& pokemon) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "nombre de enemigo     ";

    //SetConsoleTextAttribute(hConsole, 12);
    std::cout << "nivel de salud ";
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << pokemon.GetHealth() << std::endl;
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "              atacar" << std::endl;
    std::cout << "              capturar" << std::endl;
    std::cout << "              huir" << std::endl;

    SetConsoleTextAttribute(hConsole, 7);
}

void FunctionThatStartsCombat(Pokemon* pokemons, int allPokemons, Player me, bool& fighting, int& currentPokemonNum) {

    for (int _i = 0; _i < allPokemons; _i++)
    {
        //if (me.GetMyPlace() == pokemons[_i].GetSquare()) {
            for (int i = POKE_COMBAT_AREA_MIN; i < POKE_COMBAT_AREA_MAX; i++)
            {
                for (int j = POKE_COMBAT_AREA_MIN; j < POKE_COMBAT_AREA_MAX; j++)
                {
                    if (me.GetX() + j == pokemons[_i].GetPosX() && me.GetY() + i == pokemons[_i].GetPosY())
                    {
                        currentPokemonNum = _i;
                        fighting = true; 
                    }
                }
            }
        //}
    }
}

int main()
{
    Player me;
    char** map;
    GameStates state;
    bool fighting = false;

    int currentPokemonNum = 0;

    int pokemonAround1 = 0;
    int pokemonNeeded1 = 0;
    int pokemonAround2 = 0;
    int pokemonNeeded2 = 0;

    int maxPokeballs = 12;
    Pokeball *pokeballs = new Pokeball[maxPokeballs];


    std::string linea;
    
    
    int width = 0;
    int height = 0;
    int pikachuDamage = 0;
    int pokemonMaxHealth = 0;
    int mewTwoHealht = 0;
    int minWaitTurns = 0;
    int maxWaitTurns = 0;

    switch (state.ReturnGameState())
    {
    case CurrentGameState::Init :
        
        
        break;

    case CurrentGameState::Menu:

        break;


    case CurrentGameState::Game :
        
        break;

    case CurrentGameState::GameOver:

        break;


    default:
        break;
    }





    //READ DOCUMENT
    if (archivo.is_open()) {

        while (std::getline(archivo, linea) && linesToRead < 10) {

            bool leftNumber = true;

            if (linesToRead == 0) // obtener las dimensiones estipuladas
                CheckNumbers(linea, width, height, leftNumber);

            else if (linesToRead == 1) // obtener el numero de los pokemon del principio
                CheckNumbers(linea, pokemonAround1, pokemonNeeded1, leftNumber);

            else if (linesToRead == 2) // obtener el numero de los pokemon de la segunda zona
                CheckNumbers(linea, pokemonAround2, pokemonNeeded2, leftNumber);

            else if (linesToRead == 3) // obtener el daño de pikachu
                CheckOneNumber(linea, pikachuDamage);

            else if (linesToRead == 4) // obtener la vida de los pokemon salvages y la vida de MewTwo // 5;15
                CheckNumbers(linea, pokemonMaxHealth, mewTwoHealht, leftNumber);

            else if (linesToRead == 5) // obtenener el mínimo y máximo para que se muevan los pokemon
                CheckNumbers(linea, minWaitTurns, maxWaitTurns, leftNumber);

            linesToRead++;
        }
    }
    else {
        std::cerr << "No hay documento abierto";
    }

    archivo.close();

    int allPokemonAround = pokemonAround1 + pokemonAround2 + 1;

    Pokemon* pokemons = new Pokemon[allPokemonAround];

    srand(time(NULL));

    
    // DEFINE SIZE OF MAP
    map = new char*[height]; 
                                
    for (int i = 0; i < height; i++)
    {
        map[i] = new char[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (i == width / 2 && j <= height / 2) {
                map[i][j] = 'X';
            }
            else if (i >= width / 2 && j == height / 2) {
                map[i][j] = 'X';
            }
            else if (i == width / 2 && j >= height / 2) {
                map[i][j] = 'X';
            }
            else if (i <= width / 2 && j == height / 2) {
                map[i][j] = 'X';
            }
            else
                map[i][j] = '-';
        }
    }

    for (int i = 0; i < maxPokeballs; i++) {
        RandomizePokeball(pokeballs[i], maxPokeballs, i, width, height);
    }

    for (int i = 0; i < allPokemonAround; i++)
    {
        pokemons[i].SetHealth(pokemonMaxHealth);
        if (i < pokemonAround1)
            pokemons[i].SetPlace(0);
        else
            pokemons[i].SetPlace(1);

        pokemons[i].DefineMinsAndMaxs(width, height);
        pokemons[i].SetTimeForNextMove(minWaitTurns, maxWaitTurns);
        pokemons[i].RandomizePokemon();

        if (i == pokemonAround1 + pokemonAround2)
        {
            pokemons[i].SetHealth(mewTwoHealht);
            pokemons[i].SetPlace(2);
            pokemons[i].SetPosX((width / 4) * 3);
            pokemons[i].SetPosY((height / 4) * 3);
            pokemons[i].SetMewtwoNature();
        }
    }
    /*mewtwo.SetHealth(mewTwoHealht);
    mewtwo.SetPlace(2);
    mewtwo.SetPosX((width / 4) * 3);
    mewtwo.SetPosY((height / 4) * 3);*/
    //pokemons[allPokemonAround] = mewtwo;

    while (!GetAsyncKeyState(VK_ESCAPE)) {

        system("cls");
        if (fighting == true) {
            if (GetAsyncKeyState(VK_SPACE)) {
                if (me.GetPokeballs() > 0) {
                    if (CheckIfPokemonIsCapturable(pokemons[currentPokemonNum], width, height, fighting) == true)
                    {
                        fighting = false;
                        me.CapturePokemon();
                    }
                    else
                        me.DecreasePokeballs();
                    
                    //DamagePokemon(pokemons[currentPokemonNum], width, height, fighting, pikachuDamage, pokemonMaxHealth);

                    if (me.ShowCapturedPokemon() >= pokemonNeeded2) {
                        for (int i = 0; i < height; i++)
                        {
                            for (int j = 0; j < width; j++)
                            {
                                if (i > width / 2 && j == height / 2) {
                                    map[i][j] = '-';
                                }
                            }
                        }
                    }
                    else if (me.ShowCapturedPokemon() >= pokemonNeeded1) {
                        for (int i = 0; i < height; i++)
                        {
                            for (int j = 0; j < width; j++)
                            {
                                if (i == width / 2 && j < height / 2) {
                                    map[i][j] = '-';
                                }
                            }
                        }
                    }
                }
            }
            else if (GetAsyncKeyState(VK_SHIFT)) {
                DamagePokemon(pokemons[currentPokemonNum], width, height, fighting, pikachuDamage, pokemonMaxHealth);

            }
            else if (GetAsyncKeyState(VK_BACK)) {
                fighting = false;
            }
            
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {

            me.SetDirection('>');

            if (me.GetY() + 1 <= width -1 && map[me.GetY() + 1][me.GetX()] == '-')
                me.SetPosition(me.GetX(), me.GetY() + 1);

            FunctionThatStartsCombat(pokemons, allPokemonAround, me, fighting, currentPokemonNum);
        }
        else if (GetAsyncKeyState(VK_LEFT)) {

            me.SetDirection('<');

            if (me.GetY() - 1 >= 0 && map[me.GetY() - 1][me.GetX()] == '-')
                me.SetPosition(me.GetX(), me.GetY() - 1);

            FunctionThatStartsCombat(pokemons, allPokemonAround, me, fighting, currentPokemonNum);
        }
        else if (GetAsyncKeyState(VK_DOWN)) {

            me.SetDirection('v');

            if (me.GetX() + 1 <= height -1 && map[me.GetY()][me.GetX() + 1] == '-')
                me.SetPosition(me.GetX() + 1, me.GetY());

            FunctionThatStartsCombat(pokemons, allPokemonAround, me, fighting, currentPokemonNum);
        }
        else if (GetAsyncKeyState(VK_UP)) {

            me.SetDirection('^');

            if (me.GetX() - 1 >= 0 && map[me.GetY()][me.GetX() - 1] == '-')
                me.SetPosition(me.GetX() - 1, me.GetY());

            FunctionThatStartsCombat(pokemons, allPokemonAround, me, fighting, currentPokemonNum);
        }
        
        

        for (int i = 0; i < maxPokeballs; i++) {
            if (me.GetX() == pokeballs[i].posX && me.GetY() == pokeballs[i].posY) {
                me.IncreasePokeballs();


                RandomizePokeball(pokeballs[i], maxPokeballs, i, width, height);
            }
        }
        

        
        if (fighting == false)
        {
            for (int i = 0; i < allPokemonAround; i++)
            {
                pokemons[i].Move();
            }
        }
        


        int lowerX = me.GetX() - 5;
        int higherX = me.GetX() + 5;
        int lowerY = me.GetY() - 5;
        int higherY = me.GetY() + 5;

        lowerX < 0 ?
            higherX += abs(lowerX), lowerX = 0
            :
            0;
        higherX > width ?
            lowerX -= higherX - width, higherX = width
            :
            0;

        lowerY < 0 ?
            higherY += abs(lowerY), lowerY = 0
            :
            0;
        higherY > height ?
            lowerY -= higherY - height, higherY = height
            :
            0;

        

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "Pokémons capturados:";
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << me.ShowCapturedPokemon() << '/' << pokemonNeeded1;

        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "   Pokeballs:";
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << me.GetPokeballs() << std::endl;

        SetConsoleTextAttribute(hConsole, 7);
        for (int i = lowerX; i < higherX; i++) {

            std::cout << "      ";

            for (int j = lowerY; j < higherY; j++) {
                
                std::cout << ' ';
                
                if (i == me.GetX() && j == me.GetY())
                    std::cout << me.GetDir();
                else if (PutPokemon(pokemons, allPokemonAround, i, j))
                    std::cout << 'P';
                else if (i == pokemons[allPokemonAround - 1].GetPosX() && j == pokemons[allPokemonAround - 1].GetPosY())
                    std::cout << 'M';
                else if (PutPokeball(pokeballs, maxPokeballs, i, j))
                    std::cout << 'O';
                else
                    std::cout << map[j][i];
            }

            std::cout << std::endl;
        }

        if (fighting == true) 
            ShowCombatOptions(pokemons[currentPokemonNum]);
        
        CleanKeys();

        Sleep(MILLIS_FOR_NEXT_FRAME);
    }
    
    for (int i = 0; i < height; i++) {
        delete [] map[i];
    }

    delete[] map;
    

   
}

