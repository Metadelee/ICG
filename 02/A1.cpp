//--------------------------------------------------------------------------------------
//
// Subject      : Computer Graphics
// Project      : Sheet 2 : Exercise 1 Preprocessor
// Authors      : Lina Gundelwein,  Letitia Parcalabescu, Anushalakshmi Manila
// Date     	: Nov 3, 2016
// Description  : Use the SQUARE macro and alter it for correct results.
//
//--------------------------------------------------------------------------------------
// compiled with g++ -std=c++11

#include <iostream>
#include <cmath>

/*
Results for #define SQUARE(a) a*a 
For x = 1 we have f(1) = 1, g(1) = -1 and h(1) = 1
For x = 2 we have f(2) = 4, g(2) = -3 and h(2) = 1
For x = 3 we have f(3) = 9, g(3) = -5 and h(3) = 1
For x = 4 we have f(4) = 16, g(4) = -7 and h(4) = 1
For x = 5 we have f(5) = 25, g(5) = -9 and h(5) = 1
For x = 6 we have f(6) = 36, g(6) = -11 and h(6) = 1
For x = 7 we have f(7) = 49, g(7) = -13 and h(7) = 1
For x = 8 we have f(8) = 64, g(8) = -15 and h(8) = 1
For x = 9 we have f(9) = 81, g(9) = -17 and h(9) = 1
For x = 10 we have f(10) = 100, g(10) = -19 and h(10) = 1

With the above definition g and h return wrong results, because the macro only
does the textual replacement and thus you end up with
g(1) = 1-1*1-1 = -1
g(2) = 1-2*1-2 = -3
...
h(1) = 1./1*1 = 1
h(2) = 1./2*2 = 1
...
*/
//
#define SQUARE(a) ((a)*(a))

using namespace std;

float f(float x)
{

    return SQUARE(x);
}

float g(float x)
{
	return SQUARE(1-x);
}

float h(float x)
{
	return 1./SQUARE(x);
}

int main () 
{
	for(int n = 1; n < 11; n++)
        {
            cout << "For x = "<< n << " we have f(" << n << ") = " << f(n) << ", g(" << n << ") = " << g(n) << " and h(" << n << ") = " << h(n) << "\n";
        }

    
}
