#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "Player.h"
#include "GameStates.h"
#include "Pokemon.h"
#include "Pokenti.h"
#include "GameSettings.h"
#include "Pokeball.h"

const int MAX_MAP = 3;
const int CHAR_NUM_TO_NUM = 48;
const int POKE_COMBAT_AREA_MIN = -1;
const int POKE_COMBAT_AREA_MAX = 2;
const int POKEBALL_IN_MAP = 12;

const int MILLIS_FOR_NEXT_FRAME = 100;
const int MILLIS_FOR_WAIT_FOR_INIT = 3000;
const int MILLIS_FOR_WAIT_FOR_GAMEOVER = 5000;

const int SQUARE0 = 0;
const int SQUARE1 = 1;
const int SQUARE2 = 2;
const int SQUARE3 = 3;

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

std::ifstream archivo("config.txt");
int linesToRead = 0;


int main()
{
    GameSettings gameSettings;

    Player me;
    char** map;
    GameStates state;


    gameSettings.currentPokemonIndex = 0;


    gameSettings.maxPokeballs = POKEBALL_IN_MAP;
    Pokeball *pokeballs = new Pokeball[gameSettings.maxPokeballs];


    std::string linea;
    
    
    //READ DOCUMENT
    if (archivo.is_open()) {

        while (std::getline(archivo, linea) && linesToRead < 10) {

            bool leftNumber = true;

            if (linesToRead == 0) // obtener las dimensiones estipuladas
                CheckNumbers(linea, gameSettings.width, gameSettings.height, leftNumber);

            else if (linesToRead == 1) // obtener el numero de los pokemon del principio
                CheckNumbers(linea, gameSettings.pokemonAround1, gameSettings.pokemonNeeded1, leftNumber);

            else if (linesToRead == 2) // obtener el numero de los pokemon de la segunda zona
                CheckNumbers(linea, gameSettings.pokemonAround2, gameSettings.pokemonNeeded2, leftNumber);

            else if (linesToRead == 3) // obtener el da�o de pikachu
                CheckOneNumber(linea, gameSettings.pikachuDamage);

            else if (linesToRead == 4) // obtener la vida de los pokemon salvages y la vida de MewTwo 
                CheckNumbers(linea, gameSettings.pokemonMaxHealth, gameSettings.mewTwoHealht, leftNumber);

            else if (linesToRead == 5) // obtenener el m�nimo y m�ximo para que se muevan los pokemon
                CheckNumbers(linea, gameSettings.minWaitTurns, gameSettings.maxWaitTurns, leftNumber);

            linesToRead++;
        }
    }
    else {
        std::cerr << "No hay documento abierto";
    }

    archivo.close();

    gameSettings.allPokemonAround = gameSettings.pokemonAround1 + gameSettings.pokemonAround2 + 1;

    Pokemon* pokemons = new Pokemon[gameSettings.allPokemonAround];

    srand(time(NULL));

    
    // DEFINE SIZE OF MAP
    map = new char*[gameSettings.height]; 
                                
    for (int i = 0; i < gameSettings.height; i++)
    {
        map[i] = new char[gameSettings.width];
    }

    while (!GetAsyncKeyState(VK_ESCAPE) && !gameSettings.gameOver) {

        switch (state.ReturnGameState())
        {
        case CurrentGameState::Init:
            std::cout << std::endl << std::endl << std::endl;
            std::cout << "      POKENTI" << std::endl;

            for (int i = 0; i < gameSettings.height; i++)
            {
                for (int j = 0; j < gameSettings.width; j++)
                {

                    if (i == gameSettings.width / 2 && j <= gameSettings.height / 2) {
                        map[i][j] = 'X';
                    }
                    else if (i >= gameSettings.width / 2 && j == gameSettings.height / 2) {
                        map[i][j] = 'X';
                    }
                    else if (i == gameSettings.width / 2 && j >= gameSettings.height / 2) {
                        map[i][j] = 'X';
                    }
                    else if (i <= gameSettings.width / 2 && j == gameSettings.height / 2) {
                        map[i][j] = 'X';
                    }
                    else
                        map[i][j] = '-';
                }
            }

            for (int i = 0; i < gameSettings.maxPokeballs; i++) {
                RandomizePokeball(pokeballs[i], gameSettings.maxPokeballs, i, gameSettings.width, gameSettings.height);
            }

            for (int i = 0; i < gameSettings.allPokemonAround; i++)
            {
                pokemons[i].SetHealth(gameSettings.pokemonMaxHealth);
                if (i < gameSettings.pokemonAround1)
                    pokemons[i].SetPlace(0);
                else if (i < gameSettings.pokemonAround2)
                    pokemons[i].SetPlace(1);

                pokemons[i].DefineMinsAndMaxs(gameSettings.width, gameSettings.height);
                pokemons[i].SetTimeForNextMove(gameSettings.minWaitTurns, gameSettings.maxWaitTurns);
                pokemons[i].RandomizePokemon();

                if (i == gameSettings.pokemonAround1 + gameSettings.pokemonAround2)
                {
                    pokemons[i].SetHealth(gameSettings.mewTwoHealht);
                    pokemons[i].SetPlace(2);
                    pokemons[i].SetPosX((gameSettings.width / 4) * 3);
                    pokemons[i].SetPosY((gameSettings.height / 4) * 3);
                    pokemons[i].SetMewtwoNature();
                    pokemons[i].SetMewtwoName();
                    pokemons[i].SetMewtwoDifficulty();
                }
            }
            me.SetPosition(0, 0);


            Sleep(MILLIS_FOR_WAIT_FOR_INIT);

            CleanKeys();

            state.ChangeCurrentState(CurrentGameState::Menu);
            break;

        case CurrentGameState::Menu:
            system("cls");

            std::cout << "Press SPACE to play" << std::endl << std::endl;
            std::cout << "Press ESC to leave" << std::endl << std::endl;


            if (GetAsyncKeyState(VK_SPACE))
            {
                state.ChangeCurrentState(CurrentGameState::Game);
            }
            break;


        case CurrentGameState::Game:
            system("cls");
            if (gameSettings.fighting == true) {
                if (GetAsyncKeyState(VK_SPACE)) {
                    if (me.GetPokeballs() > 0) {
                        if (CheckIfPokemonIsCapturable(pokemons[gameSettings.currentPokemonIndex], gameSettings.pokemonMaxHealth, gameSettings.width, gameSettings.height, gameSettings.fighting) == true)
                        {
                            pokemons[gameSettings.currentPokemonIndex].IsMewtwoCaptured(gameSettings.hasMewtwo);
                            gameSettings.fighting = false;
                            me.CapturePokemon();
                        }
                        else
                            me.DecreasePokeballs();

                        if (me.GetX() > gameSettings.width / 2 && me.GetY() > gameSettings.height / 2 && gameSettings.fighting == false) {
                            for (int i = 0; i < gameSettings.height; i++)
                            {
                                for (int j = 0; j < gameSettings.width; j++)
                                {
                                    if (i == gameSettings.width / 2 && j > gameSettings.height / 2) {
                                        map[i][j] = '-';
                                    }
                                }
                            }
                        }
                        else if (me.ShowCapturedPokemon() >= gameSettings.pokemonNeeded2 + gameSettings.pokemonNeeded1) {
                            for (int i = 0; i < gameSettings.height; i++)
                            {
                                for (int j = 0; j < gameSettings.width; j++)
                                {
                                    if (i > gameSettings.width / 2 && j == gameSettings.height / 2) {
                                        map[i][j] = '-';
                                    }
                                }
                            }
                        }
                        else if (me.ShowCapturedPokemon() >= gameSettings.pokemonNeeded1) {
                            for (int i = 0; i < gameSettings.height; i++)
                            {
                                for (int j = 0; j < gameSettings.width; j++)
                                {
                                    if (i == gameSettings.width / 2 && j < gameSettings.height / 2) {
                                        map[i][j] = '-';
                                    }
                                }
                            }
                        }                        
                    }
                }
                else if (GetAsyncKeyState(VK_SHIFT)) {
                    
                    if (me.GetX() > gameSettings.width / 2 && me.GetY() > gameSettings.height / 2 &&
                        pokemons[gameSettings.currentPokemonIndex].GetHealth() - gameSettings.pikachuDamage <= 0) {
                        for (int i = 0; i < gameSettings.height; i++)
                        {
                            for (int j = 0; j < gameSettings.width; j++)
                            {
                                if (i == gameSettings.width / 2 && j > gameSettings.height / 2) {
                                    map[i][j] = '-';
                                }
                            }
                        }
                    }
                    
                    DamagePokemon(pokemons[gameSettings.currentPokemonIndex], gameSettings.fighting, gameSettings.pikachuDamage, gameSettings.pokemonMaxHealth);

                }
                else if (GetAsyncKeyState(VK_BACK)) {
                    gameSettings.fighting = false;

                    if (me.GetX() > gameSettings.width / 2 && me.GetY() > gameSettings.height / 2) {
                        pokemons[gameSettings.currentPokemonIndex].RandomizePokemon();

                        for (int i = 0; i < gameSettings.height; i++)
                        {
                            for (int j = 0; j < gameSettings.width; j++)
                            {
                                if (i == gameSettings.width / 2 && j > gameSettings.height / 2) {
                                    map[i][j] = '-';
                                }
                            }
                        }
                    }
                }

            }
            else if (GetAsyncKeyState(VK_RIGHT)) {

                me.SetDirection('>');

                if (me.GetY() + 1 <= gameSettings.width - 1 && map[me.GetY() + 1][me.GetX()] == '-')
                    me.SetPosition(me.GetX(), me.GetY() + 1);

                FunctionThatStartsCombat(pokemons, gameSettings.allPokemonAround, me, gameSettings.fighting, gameSettings.currentPokemonIndex);
            }
            else if (GetAsyncKeyState(VK_LEFT)) {

                me.SetDirection('<');

                if (me.GetY() - 1 >= 0 && map[me.GetY() - 1][me.GetX()] == '-')
                    me.SetPosition(me.GetX(), me.GetY() - 1);

                if (me.IsInLeague(gameSettings.width, gameSettings.height)) {
                    state.ChangeCurrentState(CurrentGameState::GameOver);                        
                }

                FunctionThatStartsCombat(pokemons, gameSettings.allPokemonAround, me, gameSettings.fighting, gameSettings.currentPokemonIndex);
            }
            else if (GetAsyncKeyState(VK_DOWN)) {

                me.SetDirection('v');

                if (me.GetX() + 1 <= gameSettings.height - 1 && map[me.GetY()][me.GetX() + 1] == '-')
                    me.SetPosition(me.GetX() + 1, me.GetY());

                FunctionThatStartsCombat(pokemons, gameSettings.allPokemonAround, me, gameSettings.fighting, gameSettings.currentPokemonIndex);
            }
            else if (GetAsyncKeyState(VK_UP)) {

                me.SetDirection('^');

                if (me.GetX() - 1 >= 0 && map[me.GetY()][me.GetX() - 1] == '-')
                    me.SetPosition(me.GetX() - 1, me.GetY());

                FunctionThatStartsCombat(pokemons, gameSettings.allPokemonAround, me, gameSettings.fighting, gameSettings.currentPokemonIndex);
            }



            for (int i = 0; i < gameSettings.maxPokeballs; i++) {
                if (me.GetX() == pokeballs[i].posX && me.GetY() == pokeballs[i].posY) {
                    me.IncreasePokeballs();


                    RandomizePokeball(pokeballs[i], gameSettings.maxPokeballs, i, gameSettings.width, gameSettings.height);
                }
            }



            if (gameSettings.fighting == false)
            {
                for (int i = 0; i < gameSettings.allPokemonAround; i++)
                {
                    pokemons[i].Move();
                }
            }



            gameSettings.lowerX = me.GetX() - 5;
            gameSettings.higherX = me.GetX() + 5;
            gameSettings.lowerY = me.GetY() - 5;
            gameSettings.higherY = me.GetY() + 5;

            gameSettings.lowerX < 0 ?
                gameSettings.higherX += abs(gameSettings.lowerX), gameSettings.lowerX = 0
                :
                0;
            gameSettings.higherX > gameSettings.width ?
                gameSettings.lowerX -= gameSettings.higherX - gameSettings.width, gameSettings.higherX = gameSettings.width
                :
                0;

            gameSettings.lowerY < 0 ?
                gameSettings.higherY += abs(gameSettings.lowerY), gameSettings.lowerY = 0
                :
                0;
            gameSettings.higherY > gameSettings.height ?
                gameSettings.lowerY -= gameSettings.higherY - gameSettings.height, gameSettings.higherY = gameSettings.height
                :
                0;



            SetConsoleTextAttribute(hConsole, 12);
            std::cout << "Pokemons capturados:";
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << me.ShowCapturedPokemon();

            SetConsoleTextAttribute(hConsole, 12);
            std::cout << "   Pokeballs:";
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << me.GetPokeballs() << std::endl;

            SetConsoleTextAttribute(hConsole, 7);
            for (int i = gameSettings.lowerX; i < gameSettings.higherX; i++) {

                std::cout << "      ";

                for (int j = gameSettings.lowerY; j < gameSettings.higherY; j++) {

                    std::cout << ' ';

                    if (i == me.GetX() && j == me.GetY())
                        std::cout << me.GetDir();
                    else if (PutPokemon(pokemons, gameSettings.allPokemonAround, i, j))
                        std::cout << 'P';
                    else if (i == pokemons[gameSettings.allPokemonAround - 1].GetPosX() && j == pokemons[gameSettings.allPokemonAround - 1].GetPosY())
                        std::cout << 'M';
                    else if (PutPokeball(pokeballs, gameSettings.maxPokeballs, i, j))
                        std::cout << 'O';
                    else
                        std::cout << map[j][i];
                }

                std::cout << std::endl;
            }

            if (gameSettings.fighting == true)
                ShowCombatOptions(pokemons[gameSettings.currentPokemonIndex]);

            CleanKeys();
            break;

        case CurrentGameState::GameOver:

            system("cls");

            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            if (gameSettings.hasMewtwo == false)
                std::cout << "You could not get Mewtwo, you lost...";
            else
                std::cout << "Along with Mewtwo and all your pokemon, you dominate the Pokenti league!";
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

            Sleep(MILLIS_FOR_WAIT_FOR_GAMEOVER);
            CleanKeys();

            gameSettings.gameOver = true;

            break;


        default:
            break;
        }

        

        Sleep(MILLIS_FOR_NEXT_FRAME);
    }
    //END MAIN





    for (int i = 0; i < gameSettings.height; i++) {
        delete [] map[i];
    }

    delete[] map;
}


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

    for (int a = 0; a < allPokemonAround - 1; a++) {


        if (pokemons[a].GetPosX() == posX && pokemons[a].GetPosY() == posY) {

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

bool CheckIfPokemonIsCapturable(Pokemon& pokemon, int maxHealth, int& width, int& height, bool& fighting) {


    int random = rand() % (pokemon.GetHealth() + pokemon.GetDifficulty());

    if (random <= 1)
    {
        pokemon.SetHealth(maxHealth);
        pokemon.RandomizePokemon();

        return true;
    }

    return false;
}

void DamagePokemon(Pokemon& pokemon, bool& fighting, int damage, int maxHealth) {


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
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << std::endl;
    std::cout << pokemon.GetName() << "         " << "salud: " << pokemon.GetHealth();
    std::cout << std::endl << std::endl;

    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "      atacar(Shift Derecho)" << std::endl;
    std::cout << "      capturar(Espacio)" << std::endl;
    std::cout << "      huir(Retroceso)" << std::endl;

    SetConsoleTextAttribute(hConsole, 7);
}

void FunctionThatStartsCombat(Pokemon* pokemons, int allPokemons, Player me, bool& fighting, int& currentPokemonNum) {

    for (int _i = 0; _i < allPokemons; _i++)
    {
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

