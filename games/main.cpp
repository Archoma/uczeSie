#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
//#include <conio.h>
using namespace std;

string pozycja(int wiersz, int kolumna) {
    return "\x1b[" + to_string(wiersz) + ";" + to_string(kolumna) + "H";
}

class Prostokat{

    public:
    int wiersz, kolumna;
    int szerokosc, wysokosc;
    int kolor;
    double pozW{}, pozK{};
    friend string pozycja(int,int);
    Prostokat(){};
    Prostokat(int w, int kol, int szer, int wys, int klr){
        wiersz = w;
        kolumna = kol;
        szerokosc = szer;
        wysokosc = wys;
        kolor = klr;
        pozK = kol;
        pozW = w;

    }

void rysuj() {
    string strKolor{};
    strKolor = strKolor + "\x1b[" + to_string(kolor) + "m";
	cout << strKolor;
	cout << pozycja(wiersz, kolumna);
	cout << "\x1b(0"; //przelaczenie konsoli na znaki box
	cout << 'l' << string(szerokosc - 2, 'q') << 'k' << pozycja(wiersz + 1, kolumna);            //gorna krawedz
           for (int i = 2; i < wysokosc; ++i) {                                                                                    //boczne krawędzie 
                 cout << 'x' << string(szerokosc - 2, ' ') << 'x';
                 cout << pozycja(wiersz + i, kolumna);
          }
           cout << 'm' << string(szerokosc - 2, 'q') << 'j' << endl;                    //dolna krawedz
           cout << "\x1b(B" << endl;
    cout << "\x1b[0m";                                                                                      //Powrot do normalnego koloru
}

void ruch(double nowex, double nowey){
    this->wiersz = static_cast<int> (nowex);
    this->kolumna = static_cast<int> (pozK = pozK + nowey);
}
};


int main(){
    
    string wlkOknaTerminala = "\x1b[8;"+to_string(45)+";"+to_string(170)+"t";
    std::cout<<wlkOknaTerminala<<endl;
    std::cout<<"\x1b[?3l";
    string czyscEkran = "\x1b[2J\x1b[1;1H";
    cout<< czyscEkran;
    Prostokat a(3,15,12,5,33);
    Prostokat b(3,15,12,5,34);
    double skoky{0.3}, skokx{0.2};
    double dy{0.5}, dx{0};
    while(1){
        
        cout<< czyscEkran;
        a.rysuj();
        b.rysuj();
        dx = 12-10 * sin(a.kolumna * 2* M_PI/20);
        a.ruch(dx, dy);
        b.ruch(skokx,0);
        if(a.kolumna > 130 or a.kolumna < 2) { dy = - dy;}
        if(b.wiersz > 15 or b.wiersz < 3) skokx = -skokx;

        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }


    return 0;
}