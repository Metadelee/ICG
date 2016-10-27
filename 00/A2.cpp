//--------------------------------------------------------------------------------------
//
// Subject      : Computer Graphics
// Project      : Sheet 1 : Exercise 2 Iterative computation
// Authors      : Lina Ouro,  Letitia Parcalabescu, Anushalakshmi Manila
// Date     : Oct  26, 2016
// Description  : Compute the value of recursive function for different inputs
//
//--------------------------------------------------------------------------------------
// compiled with g++ -std=c++11

#include <iostream>
#include <cmath>
using namespace std;

float f(float a, int n)
{
    float f0 = 0.5;

    for(int i = 0; i < n; i++)
        f0 = a * f0 * (1 - f0);

    return f0;
}

int main () 
{
    float a = 2.0;
    while(a < 3.9)
    {
        for(int n = 100; n < 105; n++)
        {
            cout << "For a = "<< a << " we have f(" << n << ") = " << f(a, n) << "\n";
        }
        a += 0.1;
    }
}
