#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "Player.h"
#include <algorithm>
const int MAX_MAP = 3;

//char** map = new char*[MAX_MAP];

std::ifstream archivo("config.txt"); // Abre el archivo en modo lectura
int _i = 0;


struct Pokemon
{
    int posX;
    int posY;
};


void PutPlayer(int& i, Player& me, int width, char *map[]) {

    for (int j = 0; j < width; j++) {
        if (j == me.GetY())
            std::cout << me.GetDir();
    }
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

int GetCameraX(Player me, int height) {
    if (me.GetX() <= 5) {
        return 0;
    }
    else if (me.GetX() >= height - 5) {
        return height - 5;
    }
    else
    {
        return me.GetX()-5;
    }
}


int GetCameraY(Player me, int width) {

    if (me.GetY() <= 5) {
        return 0;
    }
    else if (me.GetY() >= width - 5) {
        return width - 5;
    }
    else
    {
        return me.GetY()-5;
    }

    /*
    

        
    
    */

}

/*
void mostrarVista(char** mapa, int x, int y, int anchoVista, int altoVista,int width, int height) {
    // Calcular los límites de la vista
    int minX = (x - anchoVista / 2 > 0) ? x - anchoVista / 2 : 0;
    int minY = (y - altoVista / 2 > 0) ? y - altoVista / 2 : 0;
    int maxX = (x + anchoVista / 2 < width) ? x + anchoVista / 2 : width;
    int maxY = (y + altoVista / 2 < height) ? y + altoVista / 2 : height;

    // Mostrar la vista
    for (int i = minY; i < maxY; ++i) {
        for (int j = minX; j < maxX; ++j) {
            if (i == x && j == y)
                std::cout << "P";
            else
                std::cout << mapa[j][i] << " ";
        }
        std::cout << std::endl;
    }
}
*/

int main()
{
    Player me;
    char** map;
    
    int pokemonAround1 = 0;
    int pokemonNeeded1 = 0;
    int pokemonAround2 = 0;
    int pokemonNeeded2 = 0;


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


    std::cout << width << ' ' << height << std::endl << std::endl;
    std::cout << pokemonAround1 << ' ' << pokemonNeeded1 << std::endl << std::endl;
    std::cout << pokemonAround2 << ' ' << pokemonNeeded2 << std::endl << std::endl;

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
            map[i][j] = '-';
        }
    }


    char dir = '-';

    while (dir != 'q') {

        system("cls");

        switch (dir)
        {
        case 'd':
            me.SetDirection('>');
            
            if (me.GetY() + 1 <= width)
                me.SetPosition(me.GetX(), me.GetY() + 1);
            
            break;

        case 'a':
            me.SetDirection('<');
            
            if (me.GetY() - 1 >= 0)
                me.SetPosition(me.GetX(), me.GetY() - 1);

            break;

        case 's':
            me.SetDirection('v');
            
            if (me.GetX() + 1 <= height)
                me.SetPosition(me.GetX() + 1, me.GetY());

            break;

        case 'w':
            me.SetDirection('^');
            
            if (me.GetX() - 1 >= 0)
                me.SetPosition(me.GetX() - 1, me.GetY());

            break;

        default:
            break;
        }

        //
        
        //mostrarVista(map, me.GetX(), me.GetY(), 5, 5, width, height);
        //GET ALL CHARS from array TO 0
        
        //NOW I HAVE TO GET THE CENTER OF THE PLAYER IF POSSIBLE GETX -5 AND GETY -5 FOR EXAMPLE
        
        //

        int getCamPosX = GetCameraX(me, height);
        int getCamPosY = GetCameraY(me, width);


        //DrawMap
        for (int i = getCamPosX; i < getCamPosX+10 ; i++) {

                for (int j = getCamPosY; j < getCamPosY+10; j++) {
                   
                        //j >= me.GetY() - 5 - (width - me.GetY())  
                        if (i == me.GetX() && j == me.GetY())
                            PutPlayer(i, me, width, map);
                        else {
                            std::cout << map[i][j];
                        }

                        
                    
                }
                

                std::cout << std::endl;
           

            
            
            
        }
        std::cout << me.GetX() << GetCameraX(me,height);
        std::cin >> dir;

        Sleep(25);
    }
    

        


    //We delete map from stack
    for (int i = 0; i < MAX_MAP; i++) {
        delete[] map[i];
    }

    delete[] map;

   
}

