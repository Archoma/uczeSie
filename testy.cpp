#include <iostream>  
#include <string>  
#include <vector>  
#include <ctime>  
using namespace std;  

template <typename Z> Z losuj(Z min, Z max);
template <> int losuj(int min, int max){
    return min + rand()%(max - min + 1);
}

template <> double losuj(double min, double max){
    return min + static_cast<double>(rand())/RAND_MAX * (max - min);
}

template <typename T> vector<T> generuj(int ile, T min, T max){
    vector<T> roboczy;
    for(int i=0; i<ile; ++i) 
        roboczy.push_back(losuj(min,max));
    return roboczy;

}


int main() {  
    srand(time(NULL)); 
    vector<int> dziala = generuj(50000, -10000, 10000);
    vector<double> tutez = generuj(5, -20.0, 5.75);
    cout<<"Wektor int:\n";
    for(auto element : dziala) cout<<element<<" ";
    cout<<"\nWektor double:\n";
    for(auto element : tutez) cout<<element<<" ";
    cout<<endl<<endl;
//Wyszukanie minimum i maksimum metoda jednoczesnego wyszukiwania minimum i maksimum
    int maks , minim ;
    if(dziala[0]<dziala[1])
        { maks = dziala[1]; minim = dziala[0];}
    else
        { maks = dziala[0]; minim = dziala[1];}

    for(int i=2; i<dziala.size()-1; i += 2){
        if(dziala[i]<dziala[i+1]) 
            {
                if(dziala[i+1]> maks) maks = dziala[i+1];
                if(dziala[i]< minim) minim = dziala[i];
            }
        else
            {
                if(dziala[i+1]< minim) minim = dziala[i+1];
                if(dziala[i]> maks) maks = dziala[i];
            }
    }
    if(dziala.size()%2 != 0 )
    {
        if(dziala[dziala.size()-1]>maks) maks = dziala[dziala.size()-1];
        
         if(dziala[dziala.size()]< minim) minim = dziala[dziala.size()-1];
    }
    //koniec wyszukiwania minimum i maksimum

    cout<<"\nMinimum wynosi: "<<minim<<" Maksimum wynosi: "<<maks<<endl<<endl;
    
    int rozpietosc_zbioru = maks - minim + 1;

    vector<int> kubelki(rozpietosc_zbioru);

    //zliczanie wartości do "kubelkow"
    for(auto element : dziala) {
        kubelki[element - minim]++;
    }
    //koniec zliczania

    //Wyswietlenie posortowanego zbioru
    //Zamiast wyswietlania mozna zrobic podstawienie do wektora z elementami do posortowania
    cout<<"\nPosortowana tablica: \n";
    for(int liczba = 0; liczba < kubelki.size(); ++liczba){
        if(kubelki[liczba]>0) {
            if(kubelki[liczba]>1){
                 for(int i = 0; i < kubelki[liczba]; ++i)
                    cout<<liczba + minim<<" ";}
            else {cout<<liczba + minim<<" ";}
        }

    }
    cout<<endl<<endl;



    return 0;
} 