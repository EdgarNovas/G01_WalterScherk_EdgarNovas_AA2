#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "Player.h"
#include "GameStates.h"


const int MAX_MAP = 3;
const int CHAR_NUM_TO_NUM = 48;
const int POKE_COMBAT_AREA_MIN = -1;
const int POKE_COMBAT_AREA_MAX = 2;

//char** map = new char*[MAX_MAP];

std::ifstream archivo("config.txt"); // Abre el archivo en modo lectura
int _i = 0;


struct Pokemon
{
    int posX;
    int posY;
    int health;
    enum Place
    {
        PALET,
        FOREST
    };

    Place myplace;
};

struct Pokeball {
    int posX = 2;
    int posY = 2;
};

void PutPlayer(Player& me, int width, char **map) {

    std::cout << me.GetDir();
}



bool PutPokemon(Pokemon* pokemons, int& allPokemonAround, int& posX, int& posY) {
    
    for (int a = 0; a < allPokemonAround; a++) {


        if (pokemons[a].posX == posX && pokemons[a].posY == posY) {
                
            return true;
        }
    }

    return false;
}

bool PutPokeball(Pokeball* pokeballs, int& allPokeballAround, int& posX, int& posY) {

    for (int a = 0; a < allPokeballAround; a++) {


        if (pokeballs[a].posX == posX && pokeballs[a].posY == posY) {

            return true;
        }
    }

    return false;
}

void CheckNumbers(std::string linea, int& leftNum, int& rightNum, bool& leftNumber) {

    for (int j = 0; j < linea.size(); j++) {

        if (linea[j] != ';' && leftNumber) {
            leftNum *= 10;
            leftNum += linea[j] - CHAR_NUM_TO_NUM;
            //std::cout << width << std::endl << std::endl;


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
        num *= 10;
        num += linea[i] - 48;
    }
    
}

int CheckForPokemon(Pokemon& pokemons, int& width, int& height, bool& fighting) {

    /*for (int i = 0; i < group1 + group2; i++)
    {
        if (targetPosX == pokemons[i].posX)
        {
            if (targetPosY == pokemons[i].posY)
            {
                int random;
                random = rand() % pokemons[i].health;

                if (random <= 1)
                {
                    if (i < group1) {
                        pokemons[i].posX = rand() % ((width / 2) - 1);
                        pokemons[i].posY = rand() % ((height / 2) - 1);
                    }
                    else if (i >= group1) {
                        pokemons[i].posX = rand() % ((width / 2) - 1);
                        pokemons[i].posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1));
                    }

                    return 1;
                }
            }
        }
    }*/
    int random;
    random = rand() % pokemons.health;

    if (random <= 1)
    {
        if (pokemons.myplace == Pokemon::PALET) {
            pokemons.posX = rand() % ((width / 2) - 1);
            pokemons.posY = rand() % ((height / 2) - 1);
        }
        else if (pokemons.myplace == Pokemon::FOREST) {
            pokemons.posX = rand() % ((width / 2) - 1);
            pokemons.posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1));
        }

        return 1;
    }

    return 0;
}

void DamagePokemon(Pokemon& pokemons, int& width, int& height, bool& fighting/*, int& allPokemons, int targetPosX, int targetPosY, int& width, int& height*/) {

    std::cout << "Damaging pokemon";

    pokemons.health--;
    if (pokemons.health <= 0)
    {
        fighting = false;
        pokemons.health = 5;

        if (pokemons.myplace == Pokemon::PALET) {
            pokemons.posX = rand() % ((width / 2) - 1);
            pokemons.posY = rand() % ((height / 2) - 1);
        }
        else if (pokemons.myplace == Pokemon::FOREST) {
            pokemons.posX = rand() % ((width / 2) - 1);
            pokemons.posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1));
        }
    }

    /*for (int i = 0; i < allPokemons; i++)
    {
        if (targetPosX == pokemons[i].posX)
        {
            if (targetPosY == pokemons[i].posY)
            {
                pokemons[i].health--;
                if (pokemons[i].health <= 0)
                {
                    if (pokemons[i].myplace == Pokemon::PALET) {
                        pokemons[i].posX = rand() % ((width / 2) - 1);
                        pokemons[i].posY = rand() % ((height / 2) - 1);
                    }
                    else if (pokemons[i].myplace == Pokemon::FOREST) {
                        pokemons[i].posX = rand() % ((width / 2) - 1);
                        pokemons[i].posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1));
                    }
                }
            }
        }
    }*/
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
        if (me.GetMyPlace() == pokemons[_i].myplace) {
            for (int i = POKE_COMBAT_AREA_MIN; i < POKE_COMBAT_AREA_MAX; i++)
            {
                for (int j = POKE_COMBAT_AREA_MIN; j < POKE_COMBAT_AREA_MAX; j++)
                {
                    if (me.GetX() + j == pokemons[_i].posX && me.GetY() + i == pokemons[_i].posY)
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
    int pokemonHealth = 0;
    int mewTwoHealht = 0;
    //READ DOCUMENT
    if (archivo.is_open()) {

        while (std::getline(archivo, linea) && _i < 10) {

            bool leftNumber = true;

            if (_i == 0) // obtener las dimensiones estipuladas
                CheckNumbers(linea, width, height, leftNumber);

            else if (_i == 1) // obtener el numero de los pokemon del principio
                CheckNumbers(linea, pokemonAround1, pokemonNeeded1, leftNumber);

            else if (_i == 2) // obtener el numero de los pokemon de la segunda zona
                CheckNumbers(linea, pokemonAround2, pokemonNeeded2, leftNumber);

            else if (_i == 3) // obtener el daño de pikachu
                CheckOneNumber(linea, pikachuDamage);

            else if (_i == 4) // obtener la vida de los pokemon salvages y la vida de MewTwo // 5;15
                CheckNumbers(linea, pokemonHealth, mewTwoHealht, leftNumber);

            /*else if (_i == 5) // obtenener el mínimo y máximo para que se muevan los pokemon
                CheckNumbers(linea, width, height, leftNumber);*/

            _i++;
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
        pokemons[i].posX = rand() % ((width / 2) -1);
        pokemons[i].posY = rand() % ((height / 2) -1);

        pokemons[i].myplace = Pokemon::PALET;

        pokemons[i].health = pokemonHealth;
    }
    for (int i = pokemonAround1; i < pokemonAround1 + pokemonAround2; i++)
    {
        pokemons[i].posX = rand() % ((width / 2) - 1);
        pokemons[i].posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1)); 

        pokemons[i].myplace = Pokemon::FOREST;

        pokemons[i].health = pokemonHealth;
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



    while (!GetAsyncKeyState(VK_ESCAPE)) {

        system("cls");
        if (fighting == true) {
            if (GetAsyncKeyState(VK_SPACE)) {
                if (me.GetPokeballs() > 0) {
                    fighting = false;
                    me.CapturePokemon(CheckForPokemon(pokemons[currentPokemonNum], width, height, fighting));
                    DamagePokemon(pokemons[currentPokemonNum], width, height, fighting);

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
                DamagePokemon(pokemons[currentPokemonNum], width, height, fighting);
                /*if (me.GetDir() == '<')
                    DamagePokemon(pokemons, allPokemonAround, me.GetX(), me.GetY() - 1, width, height);
                else if (me.GetDir() == '>')
                    DamagePokemon(pokemons, allPokemonAround, me.GetX(), me.GetY() + 1, width, height);
                else if (me.GetDir() == '^')
                    DamagePokemon(pokemons, allPokemonAround, me.GetX() - 1, me.GetY(), width, height);
                else if (me.GetDir() == 'v')
                    DamagePokemon(pokemons, allPokemonAround, me.GetX() + 1, me.GetY(), width, height);*/

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
        //hacer una función para las teclas de movimiento
        //poner return 1   
        // si es return 1, comprovar todas las pokeball
        
        

        for (int i = 0; i < maxPokeballs; i++) {
            if (me.GetX() == pokeballs[i].posX && me.GetY() == pokeballs[i].posY) {
                me.IncreasePokeballs();

                if (i < maxPokeballs / 4) {
                    pokeballs[i].posX = rand() % ((width / 2) - 1);
                    pokeballs[i].posY = rand() % ((height / 2) - 1);
                }
                else if (i < maxPokeballs / 2) {
                    pokeballs[i].posX = rand() % ((width / 2) - 1);
                    pokeballs[i].posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1));
                }
                else if (i < (maxPokeballs / 4) * 3) {
                    pokeballs[i].posX = ((width / 2) + 1) + (rand() % ((width / 2) - 1));
                    pokeballs[i].posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1));
                }
                else {
                    pokeballs[i].posX = ((width / 2) + 1) + (rand() % ((width / 2) - 1));
                    pokeballs[i].posY = rand() % ((height / 2) - 1);
                }
            }
        }
        

        //GET ALL CHARS from array TO 0

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


            for (int j = lowerY; j < higherY; j++) {
                //j >= me.GetY() - 5 - (width - me.GetY())  
                if (i == me.GetX() && j == me.GetY())
                    PutPlayer(me, width, map);
                else if (PutPokemon(pokemons, allPokemonAround, i, j))
                    std::cout << 'P';
                else if (PutPokeball(pokeballs, maxPokeballs, i, j))
                    std::cout << 'O';
                else
                    std::cout << map[j][i];

                /*if (i == lowerX && j == higherY - 1 && me.ShowCapturedPokemon() < pokemonNeeded1)
                    std::cout << "          " <<
                    me.ShowCapturedPokemon() << '/' << pokemonNeeded1 << " pokemon";
                else if (i == lowerX && j == higherY - 1 && me.ShowCapturedPokemon() >= pokemonNeeded1)
                    std::cout << "          " <<
                    me.ShowCapturedPokemon() << '/' << pokemonNeeded2 << " pokemon";*/
            }


            std::cout << std::endl;
        }

        CombatOptions();

        Sleep(100);
    }
    
    //We delete map from stack
    for (int i = 0; i < height; i++) {
        delete [] map[i];
    }

    delete[] map;
    

   
}

