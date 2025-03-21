#include <iostream>
#include <csignal>
#include <sys/ioctl.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <vector>
#include "czarsy.h"
#include "Litera.h"

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

int main() {
    int kierunek = 0;
    string slowo = "AREK";
    //Czarsy alfabet;
    cout<<"\033[?25l"; // ukryj kursor
    cout<<"\033[2J\033[1;1H"<<flush;
    vector<Litera> litery;
    int startX = 5; int startY = 2;
    for(auto &el:slowo){
        litery.push_back(Litera(el, startX, startY));
        startX += litery.back().getWidth() + 1;
    }

    
    cout << "\033[10,1H" << flush;
    
    
    while(true){
        cout<<"\033[2J";
        for(auto &p : litery){
            p.moveTo(p.getPosX(), p.getPosY());
            p.drawALetter();
        }
    sleep_for(milliseconds(40));
        for(int i = 0; i < litery.size(); i++){
            litery[i].moveInDirection(kierunek, 1);
            if( (litery[i].getPosX() + litery[i].getWidth() + 1) > 75 ){
                   kierunek = (kierunek + 180)%360;

            }
            if( litery[i].getPosX() < 5){
                   kierunek = (kierunek + 180)%360;
                   litery[i].moveInDirection(kierunek, 1);
                   i--;
            }
        }
        // for(auto &p : litery){
        //     p.moveInDirection(kierunek, 1);
        //     if( (p.getPosX() + p.getWidth() + 1) > 75 ){
        //            kierunek = (kierunek + 180)%360;
        //     }
        //     if( p.getPosX() < 5){
        //            kierunek = (kierunek + 180)%360;
        //            p.moveInDirection(kierunek, 1);
        //            p = *(litery.begin());
        //     }
        // }

    }

    return 0;
}
