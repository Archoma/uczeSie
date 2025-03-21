#include <iostream>  
#include <iomanip>  
#include <string>  
using namespace std;
 
string naodfrut(string zdanie) {
    string wspak;
    int len = zdanie.length();
    for (int i = len - 1; i >= 0; i--)wspak += zdanie[i];
    return wspak;
}
 
 
 
int main() {
    string zdanie;
    cout << "Podaj zdanie: ";
    getline(cin, zdanie);
 
    
    cout << naodfrut(zdanie);
    return 0;
 
}
