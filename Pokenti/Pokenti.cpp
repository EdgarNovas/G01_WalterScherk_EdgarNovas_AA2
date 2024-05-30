#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "Player.h"
#include "GameStates.h"


const int MAX_MAP = 3;

//char** map = new char*[MAX_MAP];

std::ifstream archivo("config.txt"); // Abre el archivo en modo lectura
int _i = 0;


struct Pokemon
{
    int posX;
    int posY;
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
            leftNum += linea[j] - 48;
            //std::cout << width << std::endl << std::endl;


        }
        else if (leftNumber)
            leftNumber = false;
        else if (linea[j] != ';') {
            rightNum *= 10;
            rightNum += linea[j] - 48;
        }
        else
            leftNumber = true;
    }
}

int CheckForPokemon(Pokemon* pokemons, int& group1, int& group2, int targetPosX, int targetPosY, int& width, int& height) {

    for (int i = 0; i < group1 + group2; i++)
    {
        if (targetPosX == pokemons[i].posX)
        {
            if (targetPosY == pokemons[i].posY)
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

    return 0;
}




int main()
{
    Player me;
    char** map;
    GameStates state;

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
    /*for (int i = 0; i < maxPokeballs; i++)
    {
        pokeballs[i] = new Pokeball;
    }*/
    



    std::string linea;
    
    
    int width = 0;
    int height = 0;

    //READ DOCUMENT
    if (archivo.is_open()) {

        while (std::getline(archivo, linea) && _i < 3) {// se repite 3 veces ya que el documento tiene 3 lineas

            bool leftNumber = true;

            if (_i == 0) // obtener las dimensiones estipuladas
                CheckNumbers(linea, width, height, leftNumber);

            else if (_i == 1) // obtener el numero de los pokemon del principio
                CheckNumbers(linea, pokemonAround1, pokemonNeeded1, leftNumber);

            else if (_i == 2) // obtener el numero de los pokemon de la segunda zona
                CheckNumbers(linea, pokemonAround2, pokemonNeeded2, leftNumber);
            
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
    }
    for (int i = pokemonAround1; i < pokemonAround1 + pokemonAround2; i++)
    {
        pokemons[i].posX = rand() % ((width / 2) - 1);
        pokemons[i].posY = ((height / 2) + 1) + (rand() % ((height / 2) - 1)); 
    }


    // DEFINE SIZE OF MAP
    map = new char*[height]; //!!!!!!!!!!!!!!!!!!!width (izquierda a derecha) y height(arriba a abajo)
                                // !!!!!!!!!!!!!!!!es al reves en el ordenador
    for (int i = 0; i < height; i++)
    {
        map[i] = new char[width];
    }

    for (int i = 0; i < height; i++) // llenarlo de terreno caminable
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

        if (GetAsyncKeyState(VK_RIGHT)) {

            me.SetDirection('>');

            if (me.GetY() + 1 <= width -1 && map[me.GetY() + 1][me.GetX()] == '-')
                me.SetPosition(me.GetX(), me.GetY() + 1);
        }
        else if (GetAsyncKeyState(VK_LEFT)) {

            me.SetDirection('<');

            if (me.GetY() - 1 >= 0 && map[me.GetY() - 1][me.GetX()] == '-')
                me.SetPosition(me.GetX(), me.GetY() - 1);
        }
        else if (GetAsyncKeyState(VK_DOWN)) {

            me.SetDirection('v');

            if (me.GetX() + 1 <= height -1 && map[me.GetY()][me.GetX() + 1] == '-')
                me.SetPosition(me.GetX() + 1, me.GetY());
        }
        else if (GetAsyncKeyState(VK_UP)) {

            me.SetDirection('^');

            if (me.GetX() - 1 >= 0 && map[me.GetY()][me.GetX() - 1] == '-')
                me.SetPosition(me.GetX() - 1, me.GetY());
        }
        //hacer una función para las teclas de movimiento
        //poner return 1   
        // si es return 1, comprovar todas las pokeball
        else if (GetAsyncKeyState(VK_SPACE)) {
            if (me.GetPokeballs() > 0) {
                if (me.GetDir() == '<')
                    me.CapturePokemon(CheckForPokemon(pokemons, pokemonAround1, pokemonAround2, me.GetX(), me.GetY() - 1, width, height));
                else if (me.GetDir() == '>')
                    me.CapturePokemon(CheckForPokemon(pokemons, pokemonAround1, pokemonAround2, me.GetX(), me.GetY() + 1, width, height));
                else if (me.GetDir() == '^')
                    me.CapturePokemon(CheckForPokemon(pokemons, pokemonAround1, pokemonAround2, me.GetX() - 1, me.GetY(), width, height));
                else if (me.GetDir() == 'v')
                    me.CapturePokemon(CheckForPokemon(pokemons, pokemonAround1, pokemonAround2, me.GetX() + 1, me.GetY(), width, height));

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

        Sleep(300);
    }
    
    //We delete map from stack
    for (int i = 0; i < height; i++) {
        delete [] map[i];
    }

    delete[] map;
    

   
}

