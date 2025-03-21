#include "Litera.h"
#include <iostream>
#include <csignal>
#include <sys/ioctl.h>
#include <unistd.h>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

Litera::Litera(char pznak, int posX, int posY) : charSet(Czarsy()), znak(pznak), posX(posX), posY(posY),
realX(posX), realY(posY)
{
   std::bitset<10> p; 
   std::vector<int> lit = charSet.getLitere(znak);

   width = lit[0];
   for(int i = 0; i < 10; i++){
       tablica.push_back(std::vector<char>());
   }
   for(int i = 1; i < lit.size(); i++){
       p = lit[i];
           for(int j = width; j>= 0; j--){
               (tablica[i]).push_back(p[j] ? '#' : ' '); 
           }
   }
}

int Litera::getPosX()
{
    return posX;
}

int Litera::getPosY()
{
    return posY;
}

int Litera::getWidth(){
    return width;
}

void Litera::printInfo()
{
    cout << "Litera: " << znak << " na pozycji: " << posX << ", " << posY << ", " << "szerokosc: " << width << endl;
}

void Litera::drawALetter()
{
    int row = 1;
    for(auto &p : tablica){
        for(auto &q : p){
            cout<<q;
        }
        Litera::moveTo(posX, posY+(row++));
    }
    Litera::moveTo(posX, posY);
    cout << posX << flush;
}

void Litera::moveTo(int x, int y) {
    cout << "\033[" << y << ";" << x << "H"; cout.flush();
}

void Litera::jumpLetterTo(int x, int y)
{
    posX = x; realX = x;
    posY = y; realY = y;
}

void Litera::moveInDirection(int kierunek, double odleglosc)
{
    double realKierunek = kierunek * M_PI / 180;
    realX += odleglosc * cos(realKierunek);
    realY += odleglosc * sin(realKierunek);
    posX = round(realX);
    posY = round(realY);
}
