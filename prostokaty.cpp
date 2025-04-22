#include <iostream>
#include <vector>
#include <string>
using namespace std;

void pushOnStack(vector<int>& stos, int& sp, int value)
{
    stos.push_back(value);
    sp++;
}

void popFromStack(vector<int>& stos, int& sp)
{
    if (sp > 0)
    {
        stos.pop_back();
        sp--;
    }
}   

int topOfStack(const vector<int>& stos, int sp)
{
    if (sp > 0)
    {
        return stos[sp - 1];
    }
    return -1; // or some other error value
}

void printStack(const vector<int>& stos, int sp)
{
    for (int i = 0; i < sp; i++)
    {
        cout << stos[i] << " ";
    }
    cout << endl;
}


int main()
{
    vector<int> stosA;
    int spA = 0;
    
    vector<int> stosB;
    int spB = 0;

    pushOnStack(stosA, spA, 5);
    pushOnStack(stosA, spA, 10);
    pushOnStack(stosA, spA, 15);

    pushOnStack(stosB, spB, 3);
    pushOnStack(stosB, spB, 6);
    pushOnStack(stosB, spB, 9);

    cout << "Stos A: ";
    printStack(stosA, spA);
    cout << "Stos B: ";
    printStack(stosB, spB);

    popFromStack(stosA, spA);
    cout << "Stos A after pop: ";
    printStack(stosA, spA);
cout << "Top of Stos A: " << topOfStack(stosA, spA) << endl;



    return 0;



}