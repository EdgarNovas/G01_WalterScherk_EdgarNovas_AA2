#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "Player.h"
#include "GameStates.h"
#include "Pokemon.h"
#include "Pokenti.h"

const int MAX_MAP = 3;
const int CHAR_NUM_TO_NUM = 48;
const int POKE_COMBAT_AREA_MIN = -1;
const int POKE_COMBAT_AREA_MAX = 2;

const int MILLIS_FOR_NEXT_FRAME = 100;
const int MILLIS_FOR_WAIT_FOR_INIT = 3000;
const int MILLIS_FOR_WAIT_FOR_GAMEOVER = 5000;

const int SQUARE0 = 0;
const int SQUARE1 = 1;
const int SQUARE2 = 2;
const int SQUARE3 = 3;

std::ifstream archivo("config.txt");
int linesToRead = 0;

struct Settings {

    int w_idth = 0;
    int h_eight = 0;
    int p_ikachuDamage = 0;
    int p_okemonMaxHealth = 0;
    int m_ewTwoHealht = 0;
    int m_inWaitTurns = 0;
    int m_axWaitTurns = 0;

    int p_okemonAround1 = 0;
    int p_okemonNeeded1 = 0;
    int p_okemonAround2 = 0;
    int p_okemonNeeded2 = 0;

    bool f_ighting = false;
    bool h_asMewtwo = false;
};

int main()
{
    Settings gameSettings;

    Player me;
    char** map;
    GameStates state;
    bool fighting = false;

    bool hasMewtwo = false;

    int currentPokemonNum = 0;


    int maxPokeballs = 12;
    Pokeball *pokeballs = new Pokeball[maxPokeballs];


    std::string linea;
    
    
    bool gameOver = false;





    //READ DOCUMENT
    if (archivo.is_open()) {

        while (std::getline(archivo, linea) && linesToRead < 10) {

            bool leftNumber = true;

            if (linesToRead == 0) // obtener las dimensiones estipuladas
                CheckNumbers(linea, gameSettings.w_idth, gameSettings.h_eight, leftNumber);

            else if (linesToRead == 1) // obtener el numero de los pokemon del principio
                CheckNumbers(linea, gameSettings.p_okemonAround1, gameSettings.p_okemonNeeded1, leftNumber);

            else if (linesToRead == 2) // obtener el numero de los pokemon de la segunda zona
                CheckNumbers(linea, gameSettings.p_okemonAround2, gameSettings.p_okemonNeeded2, leftNumber);

            else if (linesToRead == 3) // obtener el da�o de pikachu
                CheckOneNumber(linea, gameSettings.p_ikachuDamage);

            else if (linesToRead == 4) // obtener la vida de los pokemon salvages y la vida de MewTwo // 5;15
                CheckNumbers(linea, gameSettings.p_okemonMaxHealth, gameSettings.m_ewTwoHealht, leftNumber);

            else if (linesToRead == 5) // obtenener el m�nimo y m�ximo para que se muevan los pokemon
                CheckNumbers(linea, gameSettings.m_inWaitTurns, gameSettings.m_axWaitTurns, leftNumber);

            linesToRead++;
        }
    }
    else {
        std::cerr << "No hay documento abierto";
    }

    archivo.close();

    int allPokemonAround = gameSettings.p_okemonAround1 + gameSettings.p_okemonAround2 + 1;

    Pokemon* pokemons = new Pokemon[allPokemonAround];

    srand(time(NULL));

    
    // DEFINE SIZE OF MAP
    map = new char*[gameSettings.h_eight]; 
                                
    for (int i = 0; i < gameSettings.h_eight; i++)
    {
        map[i] = new char[gameSettings.w_idth];
    }

    while (!GetAsyncKeyState(VK_ESCAPE) && !gameOver) {

        switch (state.ReturnGameState())
        {
        case CurrentGameState::Init:
            std::cout << std::endl << std::endl << std::endl;
            std::cout << "      POKENTI" << std::endl;
            std::cout << "      HECHO POR"<<std::endl;
            std::cout << "  Walter Scherk i Edgar Novas"<<std::endl;

            for (int i = 0; i < gameSettings.h_eight; i++)
            {
                for (int j = 0; j < gameSettings.w_idth; j++)
                {

                    if (i == gameSettings.w_idth / 2 && j <= gameSettings.h_eight / 2) {
                        map[i][j] = 'X';
                    }
                    else if (i >= gameSettings.w_idth / 2 && j == gameSettings.h_eight / 2) {
                        map[i][j] = 'X';
                    }
                    else if (i == gameSettings.w_idth / 2 && j >= gameSettings.h_eight / 2) {
                        map[i][j] = 'X';
                    }
                    else if (i <= gameSettings.w_idth / 2 && j == gameSettings.h_eight / 2) {
                        map[i][j] = 'X';
                    }
                    else
                        map[i][j] = '-';
                }
            }

            for (int i = 0; i < maxPokeballs; i++) {
                RandomizePokeball(pokeballs[i], maxPokeballs, i, gameSettings.w_idth, gameSettings.h_eight);
            }

            for (int i = 0; i < allPokemonAround; i++)
            {
                pokemons[i].SetHealth(gameSettings.p_okemonMaxHealth);
                if (i < gameSettings.p_okemonAround1)
                    pokemons[i].SetPlace(0);
                else
                    pokemons[i].SetPlace(1);

                pokemons[i].DefineMinsAndMaxs(gameSettings.w_idth, gameSettings.h_eight);
                pokemons[i].SetTimeForNextMove(gameSettings.m_inWaitTurns, gameSettings.m_axWaitTurns);
                pokemons[i].RandomizePokemon();

                if (i == gameSettings.p_okemonAround1 + gameSettings.p_okemonAround2)
                {
                    pokemons[i].SetHealth(gameSettings.m_ewTwoHealht);
                    pokemons[i].SetPlace(2);
                    pokemons[i].SetPosX((gameSettings.w_idth / 4) * 3);
                    pokemons[i].SetPosY((gameSettings.h_eight / 4) * 3);
                    pokemons[i].SetMewtwoNature();
                    pokemons[i].SetMewtwoName();
                    pokemons[i].SetMewtwoDifficulty();
                }
            }
            me.SetPosition(0, 0);

            int lowerX;
            int higherX;
            int lowerY;
            int higherY;
            HANDLE hConsole;

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
            if (fighting == true) {
                if (GetAsyncKeyState(VK_SPACE)) {
                    if (me.GetPokeballs() > 0) {
                        if (CheckIfPokemonIsCapturable(pokemons[currentPokemonNum], gameSettings.p_okemonMaxHealth, gameSettings.w_idth, gameSettings.h_eight, fighting) == true)
                        {
                            pokemons[currentPokemonNum].IsMewtwoCaptured(hasMewtwo);
                            fighting = false;
                            me.CapturePokemon();
                        }
                        else
                            me.DecreasePokeballs();

                        if (me.GetX() > gameSettings.w_idth / 2 && me.GetY() > gameSettings.h_eight / 2 && fighting == false) {
                            for (int i = 0; i < gameSettings.h_eight; i++)
                            {
                                for (int j = 0; j < gameSettings.w_idth; j++)
                                {
                                    if (i == gameSettings.w_idth / 2 && j > gameSettings.h_eight / 2) {
                                        map[i][j] = '-';
                                    }
                                }
                            }
                        }
                        else if (me.ShowCapturedPokemon() >= gameSettings.p_okemonNeeded2) {
                            for (int i = 0; i < gameSettings.h_eight; i++)
                            {
                                for (int j = 0; j < gameSettings.w_idth; j++)
                                {
                                    if (i > gameSettings.w_idth / 2 && j == gameSettings.h_eight / 2) {
                                        map[i][j] = '-';
                                    }
                                }
                            }
                        }
                        else if (me.ShowCapturedPokemon() >= gameSettings.p_okemonNeeded1) {
                            for (int i = 0; i < gameSettings.h_eight; i++)
                            {
                                for (int j = 0; j < gameSettings.w_idth; j++)
                                {
                                    if (i == gameSettings.w_idth / 2 && j < gameSettings.h_eight / 2) {
                                        map[i][j] = '-';
                                    }
                                }
                            }
                        }                        
                    }
                }
                else if (GetAsyncKeyState(VK_SHIFT)) {
                    
                    if (me.GetX() > gameSettings.w_idth / 2 && me.GetY() > gameSettings.h_eight / 2 &&
                        pokemons[currentPokemonNum].GetHealth() - gameSettings.p_ikachuDamage <= 0) {
                        for (int i = 0; i < gameSettings.h_eight; i++)
                        {
                            for (int j = 0; j < gameSettings.w_idth; j++)
                            {
                                if (i == gameSettings.w_idth / 2 && j > gameSettings.h_eight / 2) {
                                    map[i][j] = '-';
                                }
                            }
                        }
                    }
                    
                    DamagePokemon(pokemons[currentPokemonNum], fighting, gameSettings.p_ikachuDamage, gameSettings.p_okemonMaxHealth);

                }
                else if (GetAsyncKeyState(VK_BACK)) {
                    fighting = false;

                    if (me.GetX() > gameSettings.w_idth / 2 && me.GetY() > gameSettings.h_eight / 2) {
                        pokemons[currentPokemonNum].RandomizePokemon();

                        for (int i = 0; i < gameSettings.h_eight; i++)
                        {
                            for (int j = 0; j < gameSettings.w_idth; j++)
                            {
                                if (i == gameSettings.w_idth / 2 && j > gameSettings.h_eight / 2) {
                                    map[i][j] = '-';
                                }
                            }
                        }
                    }
                }

            }
            else if (GetAsyncKeyState(VK_RIGHT)) {

                me.SetDirection('>');

                if (me.GetY() + 1 <= gameSettings.w_idth - 1 && map[me.GetY() + 1][me.GetX()] == '-')
                    me.SetPosition(me.GetX(), me.GetY() + 1);

                FunctionThatStartsCombat(pokemons, allPokemonAround, me, fighting, currentPokemonNum);
            }
            else if (GetAsyncKeyState(VK_LEFT)) {

                me.SetDirection('<');

                if (me.GetY() - 1 >= 0 && map[me.GetY() - 1][me.GetX()] == '-')
                    me.SetPosition(me.GetX(), me.GetY() - 1);

                if (me.IsInLeague(gameSettings.w_idth, gameSettings.h_eight)) {
                    //if (hasMewtwo == false){
                        state.ChangeCurrentState(CurrentGameState::GameOver);                        
                    //}
                }

                FunctionThatStartsCombat(pokemons, allPokemonAround, me, fighting, currentPokemonNum);
            }
            else if (GetAsyncKeyState(VK_DOWN)) {

                me.SetDirection('v');

                if (me.GetX() + 1 <= gameSettings.h_eight - 1 && map[me.GetY()][me.GetX() + 1] == '-')
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


                    RandomizePokeball(pokeballs[i], maxPokeballs, i, gameSettings.w_idth, gameSettings.h_eight);
                }
            }



            if (fighting == false)
            {
                for (int i = 0; i < allPokemonAround; i++)
                {
                    pokemons[i].Move();
                }
            }



            lowerX = me.GetX() - 5;
            higherX = me.GetX() + 5;
            lowerY = me.GetY() - 5;
            higherY = me.GetY() + 5;

            lowerX < 0 ?
                higherX += abs(lowerX), lowerX = 0
                :
                0;
            higherX > gameSettings.w_idth ?
                lowerX -= higherX - gameSettings.w_idth, higherX = gameSettings.w_idth
                :
                0;

            lowerY < 0 ?
                higherY += abs(lowerY), lowerY = 0
                :
                0;
            higherY > gameSettings.h_eight ?
                lowerY -= higherY - gameSettings.h_eight, higherY = gameSettings.h_eight
                :
                0;



            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            std::cout << "Pok�mons capturados:";
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << me.ShowCapturedPokemon() << '/' << gameSettings.p_okemonNeeded1;

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
            break;

        case CurrentGameState::GameOver:

            system("cls");

            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            if (hasMewtwo == false)
                std::cout << "You could not get Mewtwo...";
            else
                std::cout << "Along with Mewtwo and all your pokemon, you dominate the Pokenti league!";
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

            Sleep(MILLIS_FOR_WAIT_FOR_GAMEOVER);
            CleanKeys();

            gameOver = true;

            break;


        default:
            break;
        }

        

        Sleep(MILLIS_FOR_NEXT_FRAME);
    }
    //END MAIN





    for (int i = 0; i < gameSettings.h_eight; i++) {
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
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << pokemon.GetName() << "     ";

    //SetConsoleTextAttribute(hConsole, 12);
    std::cout << "nivel de salud ";
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << pokemon.GetHealth() << std::endl;
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "              atacar(Shift Derecho)" << std::endl;
    std::cout << "              capturar(Espacio)" << std::endl;
    std::cout << "              huir(Retroceso)" << std::endl;

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

