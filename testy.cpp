

#include <iostream>
#include <vector>
using namespace std;
class Stos
{
private:
    int SP;
    int stack[100];
public:
    Stos() : SP{0} {}
    void push(int value)
    {
        stack[SP++] = value;
    }
    int pop()
    {
        return stack[--SP];
    }
    int get_SP()
    {
        return SP;
    }
};
class StosSumujacy : Stos
{
private:
    int suma;
public:
    StosSumujacy() : Stos(), suma{0} {}
    void push(int value)
    {
        suma += value;
        Stos::push(value);
    }
    int pop()
    {
        int val = Stos::pop();
        suma -= val;
        return val;
    }
    int get_suma()
    {
        return suma;
    }
};
int main(void)
{
    Stos A, B, C;
    StosSumujacy D;
    A.push(3);
    A.push(2);
    A.push(1);
    B.push(5);
    B.push(4);
    C.push(6);
    D.push(13);
    D.push(12);
    cout << A.pop() << endl;
    cout << B.pop() << endl;
    cout << C.pop() << endl;
    cout << "Suma elementow stosu D: " << D.get_suma() << endl;
    cout << "Zdejmuje ze stosu D 12: " << D.pop() << endl;
    cout << "Suma elementow stosu D: " << D.get_suma() << endl;
    //cout << "Wskaznik stosu stosu D: " << D.get_SP() << endl;
    return 0;
}

    
