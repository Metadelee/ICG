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