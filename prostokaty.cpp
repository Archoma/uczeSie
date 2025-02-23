#include <iostream>
#include <random>
 
using namespace std;
 
int losowaLiczba(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
 
    return distrib(gen);
}
 
int main() {
    int min, max;
 
    cout << "Podaj dolny zakres przedzialu: ";
    cin >> min;
 
    cout << "Podaj gorny zakres przedzialu: ";
    cin >> max;
 
    int losowa = losowaLiczba(min, max);
    cout << "Wylosowana liczba z przedzialu [" << min << ", " << max << "]: " << losowa << endl;
 
    return 0;
}