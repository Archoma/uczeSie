#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "czarsy.h"
#include <bitset>
class Litera {
    char znak;
    int posX, posY;
    int width;
    double realX, realY;
    std::vector<std::vector<char>> tablica;
    Czarsy charSet;
    public:
    Litera() = default;
    Litera(char pznak, int posX, int posY);
    int getPosX();
    int getPosY();
    int getWidth();
    void printInfo();
    void drawALetter();
    void moveInDirection(int kierunek, double odleglosc);
    void moveTo(int x, int y);
    void jumpLetterTo(int direction, int distance);
};