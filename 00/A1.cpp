//--------------------------------------------------------------------------------------
//
// Subject      : Computer Graphics
// Project      : Sheet 1 : Exercise 1 Circle calculation
// Authors      : Lina Ouro,  Letitia Parcalabescu, Anushalakshmi Manila
// Date     : Oct  26, 2016
// Description  : Compute the area and circumference of a circle with given radius
//
//--------------------------------------------------------------------------------------
// compiled with g++ -std=c++11

#include <iostream>
#include <cmath>
using namespace std;

int main () 
{
    float radius;
    float circumference;
    float area;

    cout << "Please enter the radius of a circle: ";
    cin >> radius;

    while (radius < 0) {
        cout << "Error: the radius has to be positive. Enter again an appropiate value:"<< endl;
        cin >> radius;
    }
    circumference = 2 * 3.1415 * radius;
    area = 3.1415 * radius * radius;

    cout << "\tArea= " << area << "\n" << "\tCircumference= " << circumference << "\n";

    cin.get();
}