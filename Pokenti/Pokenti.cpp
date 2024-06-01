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

const int MILLIS_FOR_NEXT_FRAME = 100;

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

void PutPlayer(Player& me, int width, char **map) {

    std::cout << me.GetDir();
}



bool PutPokemon(Pokemon* pokemons, int& allPokemonAround, int& posX, int& posY) {
    
    for (int a = 0; a < allPokemonAround; a++) {


        if (pokemons[a].GetPosX() == posX && pokemons[a].GetPosY() == posY) {
                
            return true;
        }
    }

    return false;
}


void RandomizePokemon(Pokemon& pokemon, int width, int height) {

    if(pokemon.GetSquare() == SQUARE0)
    {
        pokemon.SetPosX(rand() % ((width / 2) - 1));
        pokemon.SetPosY(rand() % ((height / 2) - 1));
    }
    else if (pokemon.GetSquare() == SQUARE1)
    {
        pokemon.SetPosX(rand() % ((width / 2) - 1));
        pokemon.SetPosY(((height / 2) + 1) + (rand() % ((height / 2) - 1)));

    }
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
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << std::endl << std::endl << num << std::endl << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
}

int CheckForPokemon(Pokemon& pokemon, int& width, int& height, bool& fighting) {

    
    int random;
    random = rand() % pokemon.GetHealth();

    if (random <= 1)
    {
        RandomizePokemon(pokemon, width, height);

        return 1;
    }

    return 0;
}

void DamagePokemon(Pokemon& pokemon, int& width, int& height, bool& fighting, int damage, int maxHealth/*, int& allPokemons, int targetPosX, int targetPosY, int& width, int& height*/) {

    std::cout << "Damaging pokemon";

    pokemon.MinusHealth(damage);
    if (pokemon.GetHealth() <= 0)
    {
        fighting = false;
        pokemon.SetHealth(maxHealth);

        RandomizePokemon(pokemon, width, height);
    }

}

void CombatOptions() {
    std::cout << "nombre de enemigo     " << "nivel de salud" << std::endl;
    std::cout << "atacar" << std::endl;
    std::cout << "capturar" << std::endl;
    std::cout << "huir" << std::endl;
}

void FunctionThatStartsCombat(Pokemon* pokemons, int allPokemons, Player me, bool& fighting, int& currentPokemonNum) {

    for (int _i = 0; _i < allPokemons; _i++)
    {
        if (me.GetMyPlace() == pokemons[_i].GetSquare()) {
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
        }
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

            else if (linesToRead == 3) // obtener el da�o de pikachu
                CheckOneNumber(linea, pikachuDamage);

            else if (linesToRead == 4) // obtener la vida de los pokemon salvages y la vida de MewTwo // 5;15
                CheckNumbers(linea, pokemonMaxHealth, mewTwoHealht, leftNumber);

            /*else if (_i == 5) // obtenener el m�nimo y m�ximo para que se muevan los pokemon
                CheckNumbers(linea, width, height, leftNumber);*/

            linesToRead++;
        }
    }
    else {
        std::cerr << "No hay documento abierto";
    }

    archivo.close();

    int allPokemonAround = pokemonAround1 + pokemonAround2;

    Pokemon* pokemons = new Pokemon[allPokemonAround];

    srand(time(NULL));

    for (int i = 0; i < pokemonAround1; i++)
    {
        pokemons[i].SetPlace(0);
        pokemons[i].SetHealth(pokemonMaxHealth);

        RandomizePokemon(pokemons[i], width, height);
    }
    for (int i = pokemonAround1; i < pokemonAround1 + pokemonAround2; i++)
    {
        pokemons[i].SetPlace(1);
        pokemons[i].SetHealth(pokemonMaxHealth);

        RandomizePokemon(pokemons[i], width, height);
    }


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


    while (!GetAsyncKeyState(VK_ESCAPE)) {

        system("cls");
        if (fighting == true) {
            if (GetAsyncKeyState(VK_SPACE)) {
                if (me.GetPokeballs() > 0) {
                    fighting = false;
                    me.CapturePokemon(CheckForPokemon(pokemons[currentPokemonNum], width, height, fighting));
                    DamagePokemon(pokemons[currentPokemonNum], width, height, fighting, pikachuDamage, pokemonMaxHealth);

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

            GetAsyncKeyState(VK_RIGHT);
            GetAsyncKeyState(VK_LEFT);
            GetAsyncKeyState(VK_DOWN);
            GetAsyncKeyState(VK_UP);
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
        std::cout << "Pok�mons capturados:";
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << me.ShowCapturedPokemon() << '/' << pokemonNeeded1;

        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "   Pokeballs:";
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << me.GetPokeballs() << std::endl;

        SetConsoleTextAttribute(hConsole, 7);
        for (int i = lowerX; i < higherX; i++) {


            for (int j = lowerY; j < higherY; j++) {
                if (i == me.GetX() && j == me.GetY())
                    PutPlayer(me, width, map);
                else if (PutPokemon(pokemons, allPokemonAround, i, j))
                    std::cout << 'P';
                else if (PutPokeball(pokeballs, maxPokeballs, i, j))
                    std::cout << 'O';
                else
                    std::cout << map[j][i];
            }

            std::cout << std::endl;
        }


        Sleep(MILLIS_FOR_NEXT_FRAME);
    }
    
    //We delete map from stack
    for (int i = 0; i < height; i++) {
        delete [] map[i];
    }

    delete[] map;
    

   
}

