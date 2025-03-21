#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

    // Unicode Box Drawing characters
    char topLeft = 0xDA, topRight = 0xBF, horizontal = 0xC4, vertical = 0xB3,
         bottomLeft = 0xC0, bottomRight = 0xD9;
    bool flaga{false};
   void InputRead();
   
   
   string makeKolor(int kolor){
        string takiKolor;
        switch (kolor) {
        case 0: takiKolor = "\e[0m"     ; break;
        case 1: takiKolor = "\e[31m"    ; break;
        case 2: takiKolor = "\x1b[32m"  ; break;
        case 3: takiKolor = "\x1b[33m"  ; break;
        case 4: takiKolor = "\e[34m"    ; break;
        case 5: takiKolor = "\e[35m"    ; break;
        case 6: takiKolor = "\e[36m"    ; break;
        case 7: takiKolor = "\e[37m"    ; break;
        case 8: takiKolor = "\e[38m"    ; break;
        }
        return takiKolor;
    }

    string poz(int x, int y){
        string poz{};
        return poz+"\e["+to_string(y)+";"+to_string(x)+"H";
    }


class Prostokat {
public:
    int id;
    int x, y; // Współrzędne lewego górnego wierzchołka
    int szerokosc, wysokosc; // Długości boków
    int kierunekX = 1, kierunekY = 1;
    bool touchFlag{false};
    string reset{};
    string kolor;
    string resetKolor = "\e[0m";
    static int IdGenerator;
    friend string poz(int x, int y);
    friend string makeKolor(int kolor);
    Prostokat() = default;
    Prostokat(int x, int y, int szerokosc, int wysokosc, int kolor) 
        : x(x), y(y), szerokosc(szerokosc), wysokosc(wysokosc){
            this->kolor = makeKolor(kolor);
        id = IdGenerator++;
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
                if((i == 0 and j == 0) || (i == 0 && j == (szerokosc - 1)) ||
                    ((i == (wysokosc - 1)) && j == 0) || (i == (wysokosc - 1) && j == (szerokosc - 1))              
                
                ) cout<<"+";
                else
                if(i == 0 || i == (wysokosc - 1) || j==0 || j== (szerokosc - 1))
                {
                    if(i==0 || i==(wysokosc - 1)) cout<<"-"<<flush; else cout<<"|"<<flush;
                    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
                } 
                else cout<<"\e[C";
            }
            cout<<poz(x,y+i+1);
        }
        cout<<poz(x,y)<<id<<" "<<flush;
    }

    void ruszaj(int x, int y){ setX(x); setY(y);}


};


int Prostokat::IdGenerator = 0;
int losuj(int min, int max){
    return min + rand()%(max - min + 1);
}


int main(){
    std::thread inputThread(InputRead);
    srand(time(NULL));
    const int ile = 25;
    int kierunekX=1, kierunekY=1;
    int zmianaX{}, zmianaY{};
    int maxSzer = 100, maxWys = 35;
    string wlkOknaTerminala = "\e[8;"+to_string(maxWys)+";"+to_string(maxSzer)+";t";
    cout<<wlkOknaTerminala;
    cout<<"\e[1;1H\e[2J";
    cout<<"\e[?25l";
    int licznik = 1;
    int x,y,w,h,k;
    char input{};
    //bool flaga{false};

    vector<Prostokat> obiekty;

    for(int i=0; i<ile; ++i){
        w = losuj(5,10);
        h = losuj(3,5);
        x = losuj(1,maxSzer - w);
        y = losuj(1, maxWys - h);
        k = losuj(1,8);
        obiekty.emplace_back(Prostokat(x,y,w,h,k));
    }
    
    // while(1){
    //     cout<<"\e[1;1H";
    //     cout<<"\e[2J";
        // Moj Statek - sterowany klawiszami    
    Prostokat MyShip(3, 23, 6, 3, k);
        int dX = 3;
        int dY = 1;
    
    system("stty raw");
    //petla animujaca gre
    while(1){
        std::cout<<"\e[1;1H"; //ustawienie kursora w pozycji o wspolrzednych 1,1
        std::cout<<"\e[2J";   //czyszczenie ekranu konsoli

        // Sterowanie i rysowanie Mojego Statku
        MyShip.rysuj();
        input = getchar(); // Odczytanie pojedynczego znaku z wejścia
        if(input == 'q') { flaga = true; }
        // // Sprawdzenie czy odczytany znak jest sekwencją znaków dla strzałki kursora
        // if (input == '\033') { // '\033' to kod ESC (escape)
        //     char arrow1 = getchar(); // Odczytanie kolejnego znaku (znak kontrolny)
        //     char arrow2 = getchar(); // Odczytanie kolejnego znaku (kod strzałki)
            
        //     if (arrow1 == '[') { // Sprawdzenie czy to jest kod strzałki
        //         switch (arrow2) {
        //             case 'A':
        //                MyShip.kierunekY = -1; MyShip.kierunekX = 0;
        //                 break;
        //             case 'B':
        //                 MyShip.kierunekY = 1; MyShip.kierunekX = 0;
        //                 break;
        //             case 'C':
        //                  MyShip.kierunekX = 1; MyShip.kierunekY = 0;
        //                 break;
        //             case 'D':
        //                   MyShip.kierunekX = -1; MyShip.kierunekY = 0;
        //                 break;
        //             default:
                        
        //                 break;
        //         }
        //     }
        // }

            if(MyShip.x + dX * MyShip.kierunekX < maxSzer - MyShip.szerokosc && MyShip.x + dX * MyShip.kierunekX >= 2) MyShip.x += MyShip.kierunekX * dX;
            if(MyShip.y + dY * MyShip.kierunekY < maxWys - MyShip.wysokosc && MyShip.y + dY * MyShip.kierunekY >= 2) MyShip.y += MyShip.kierunekY * dY;
            MyShip.ruszaj(MyShip.x, MyShip.y);

        
        std::cout<<flush;
        
    //    for(auto& obiekt: obiekty){

    //     obiekt.rysuj();
    
    //     cout<<flush;

    //     zmianaX = losuj(0,4);
    //     zmianaY = losuj(0,2);
    //     if(obiekt.x + zmianaX * obiekt.kierunekX > maxSzer - obiekt.szerokosc || obiekt.x + zmianaX * obiekt.kierunekX <= 2) obiekt.kierunekX= - obiekt.kierunekX;
    //     if(obiekt.y + zmianaY * obiekt.kierunekY > maxWys - obiekt.wysokosc || obiekt.y + zmianaY * obiekt.kierunekY <= 2) obiekt.kierunekY = - obiekt.kierunekY;
    //      obiekt.ruszaj(obiekt.x + zmianaX * obiekt.kierunekX, obiekt.y + zmianaY * obiekt.kierunekY);
        
    //     } 
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }    
    
       system("stty cooked");
       inputThread.join();
    return 0;
}

void InputRead(){
    char input{};
    system("stty raw");
        while(!flaga){
        input = getchar(); // Odczytanie pojedynczego znaku z wejścia

            // Sprawdzenie czy odczytany znak jest sekwencją znaków dla strzałki kursora
            if (input == '\033') { // '\033' to kod ESC (escape)
                char arrow1 = getchar(); // Odczytanie kolejnego znaku (znak kontrolny)
                char arrow2 = getchar(); // Odczytanie kolejnego znaku (kod strzałki)
                cout<<arrow1<<endl;
                // if (arrow1 == '[') { // Sprawdzenie czy to jest kod strzałki
                    switch (arrow2) {
                        case 'A':
                        MyShip.kierunekY = -1; MyShip.kierunekX = 0;
                            break;
                        case 'B':
                            MyShip.kierunekY = 1; MyShip.kierunekX = 0;
                            break;
                        case 'C':
                            MyShip.kierunekX = 1; MyShip.kierunekY = 0;
                            break;
                        case 'D':
                            MyShip.kierunekX = -1; MyShip.kierunekY = 0;
                            break;
                        default:
                            
                            break;
                    }
                }
            }
        }
   }
   