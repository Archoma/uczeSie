#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

class Prostokat {
public:
    int x, y; // Współrzędne lewego górnego wierzchołka
    int szerokosc, wysokosc; // Długości boków
    int kierunekX = 1, kierunekY = 1;
    bool touchFlag{false};
    string reset{};
    string kolor;
    string resetKolor = "\e[0m";
   
    string poz(int x, int y){
        string poz{};
        return poz+"\e["+to_string(x)+";"+to_string(y)+"H";
    }

    string makeKolor(int kolor){
        string takiKolor;
        switch (kolor) {
        case 0: takiKolor = resetKolor; break;
        case 1: takiKolor = "\e[31m"; break;
        case 2: takiKolor = "\x1b[32m"; break;
        case 3: takiKolor = "\x1b[33m"; break;
        case 4: takiKolor = "\e[34m"; break;
        case 5: takiKolor = "\e[35m"; break;
        case 6: takiKolor = "\e[36m"; break;
        case 7: takiKolor = "\e[37m"; break;
        case 8: takiKolor = "\e[38m"; break;
        }
        return takiKolor;
    }
    
    Prostokat() = default;
    Prostokat(int x, int y, int szerokosc, int wysokosc, int kolor) 
        : x(x), y(y), szerokosc(szerokosc), wysokosc(wysokosc){
            this->kolor = makeKolor(kolor);
        }

    bool przecinaSie(const Prostokat& inny) const {
        return (x < inny.x + inny.szerokosc && x + szerokosc > inny.x &&
                y < inny.y + inny.wysokosc && y + wysokosc > inny.y);
    }

    void setX(int liczba) {this->x=liczba;}
    void setY(int liczba) {this->y = liczba;}

    void rysuj(){
        cout<<poz(x,y)<<flush;
        if(touchFlag) cout<<makeKolor(1); else  cout<<kolor;
        for(int i=0; i < wysokosc; ++i){
            for (size_t j = 0; j < szerokosc; j++)
            {
                if(i == 0 || i == (wysokosc - 1) || j==0 || j== (szerokosc - 1))
                {
                    if(i==0 || i==(wysokosc - 1)) cout<<"-"<<flush; else cout<<"|"<<flush;
                    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
                } 
                else cout<<"\e[C";
            }
            cout<<poz(x+i+1,y);
        }
    }

    void ruszaj(int x, int y){ setX(x); setY(y);}


};

int losuj(int min, int max){
    return min + rand()%(max - min + 1);
}


int main(){
    srand(time(NULL));
    const int ile = 250;
    int kierunekX=1, kierunekY=1;
    int zmianaX{}, zmianaY{};
    cout<<"\e[8;28;110;t";
    cout<<"\e[1;1H\e[2J";
    cout<<"\e[?25l";
    int licznik = 1;
    int x,y,w,h,k;
    // Prostokat P(5,15,7,4,2);
    // Prostokat B(2,3,4,7,3);
    vector<Prostokat> obiekty;
    // obiekty.push_back(P);
    // obiekty.push_back(B);
    for(int i=0; i<ile; ++i){
        w = losuj(3,5);
        h = losuj(3,5);
        x = losuj(1,24 - h);
        y = losuj(1, 115 - w);
        k = losuj(1,8);
        obiekty.emplace_back(Prostokat(x,y,w,h,k));
    }
    
    while(1){
        cout<<"\e[1;1H";
        cout<<"\e[2J";
        
       for(auto& obiekt: obiekty){

        obiekt.rysuj();
        cout<<flush;

        zmianaX = losuj(0,2);
        zmianaY = losuj(0,4);
        if(obiekt.x + zmianaX * obiekt.kierunekX > 24 - obiekt.szerokosc || obiekt.x + zmianaX * obiekt.kierunekX <= 2) obiekt.kierunekX= - obiekt.kierunekX;
        if(obiekt.y + zmianaY * kierunekY > 100 - obiekt.wysokosc || obiekt.y + zmianaY * kierunekY <= 2) obiekt.kierunekY = - obiekt.kierunekY;
        obiekt.ruszaj(obiekt.x + zmianaX * obiekt.kierunekX, obiekt.y + zmianaY * obiekt.kierunekY);
        
        
        
        
        
        
       } 
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        //licznik=1;
    }
    return 0;
}