#include "prostokat.h"
#include <iostream>
#include <cmath>
using namespace std;
void przesunDo(int x, int y) {
    cout << "\033[" << y << ";" << x << "H"; cout.flush();
}
void Prostokat::draw() {
    przesunDo(x, y);
    for(int i = 0; i < w; i++) { cout << "*"; } cout<<flush;
    for(int j = 1; j < h - 1; j++) {
        przesunDo(x, y + j);
        cout << "*";
        przesunDo(x + w - 1, y + j);
        cout << "*";
        cout<<flush;
    }
    przesunDo(x, y + h - 1);
    for(int i = 0; i < w; i++) { cout << "*"; } cout<<flush;
    
}

void Prostokat::move(int direction, double speed)
{
    realX += speed * cos(M_PI * direction / 180);
    realY += 0.5 *  speed * sin(M_PI * direction / 180);
     x += static_cast<int>(realX) - x;
     y += static_cast<int>(realY) - y; 
}
