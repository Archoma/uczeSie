#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

string makeKolor(int kolor) {
    const string kolory[] = {"\e[0m", "\e[31m", "\x1b[32m", "\x1b[33m", "\e[34m", "\e[35m", "\e[36m", "\e[37m", "\e[38m"};
    return (kolor >= 0 && kolor < 9) ? kolory[kolor] : "\e[0m";
}

class Prostokat {
public:
    int id, x, y, szerokosc, wysokosc, kierunekX = 1, kierunekY = 1;
    bool touchFlag{false};
    string kolor;
    static int IdGenerator;

    Prostokat(int x, int y, int szerokosc, int wysokosc, int kolor) 
        : x(x), y(y), szerokosc(szerokosc), wysokosc(wysokosc), kolor(makeKolor(kolor)), id(IdGenerator++) {}

    bool przecinaSie(const Prostokat& inny) const {
        return (x < inny.x + inny.szerokosc && x + szerokosc > inny.x &&
                y < inny.y + inny.wysokosc && y + wysokosc > inny.y);
    }

    void rysuj(string &buf) {
        
        //cout<<poz(x,y)<<flush;
        buf+="\e["+to_string(y)+";"+to_string(x)+"H"+kolor;
        //if(touchFlag) cout<<makeKolor(1); else  cout<<kolor;
        
        for(int i=0; i < wysokosc; ++i){
            for (size_t j = 0; j < szerokosc; j++)
            {
                if((i == 0 && j == 0) || (i == 0 && j == (szerokosc - 1)) ||
                    ((i == (wysokosc - 1)) && j == 0) || (i == (wysokosc - 1) && j == (szerokosc - 1))              
                
                ) buf+="+";
                else
                if(i == 0 || i == (wysokosc - 1) || j==0 || j== (szerokosc - 1))
                {
                    if(i==0 || i==(wysokosc - 1)) buf+="-"; else buf+="|";
                    
                } 
                else buf+="\e[C";
            }
            buf+="\e["+to_string(y+i+1)+";"+to_string(x)+"H";
        }
        buf+="\e["+to_string(y)+";"+to_string(x)+"H"+to_string(id)+" ";
    }
    

    void ruszaj(int maxSzer, int maxWys, int zmianaX, int zmianaY) {
        if (x + zmianaX * kierunekX > maxSzer - szerokosc || x + zmianaX * kierunekX <= 6) kierunekX *= -1;
        if (y + zmianaY * kierunekY > maxWys - wysokosc || y + zmianaY * kierunekY <= 1) kierunekY *= -1;
        x += zmianaX * kierunekX;
        y += zmianaY * kierunekY;
    }
};

int Prostokat::IdGenerator = 0;
int losuj(int min, int max) { return min + rand() % (max - min + 1); }

int main() {
    srand(time(NULL));
    const int ile = 2, maxSzer = 100, maxWys = 38, opoznienie = 100;
    vector<Prostokat> obiekty;

    for (int i = 0; i < ile; ++i)
        obiekty.emplace_back(losuj(1, maxSzer - 10), losuj(1, maxWys - 5), losuj(5, 10), losuj(3, 5), losuj(1, 8));

    cout << "\e[8;" << maxWys << ";" << maxSzer << ";t\e[1;1H\e[2J\e[?25l";
    while (true) {
        string bufor = "\e[1;1H\e[2J";
        for (auto &prost : obiekty) {
            prost.rysuj(bufor);
            prost.ruszaj(maxSzer, maxWys, losuj(0, 3), losuj(0, 1));
        }
        cout << bufor << flush;
        this_thread::sleep_for(chrono::milliseconds(opoznienie));
    }
    return 0;
}
