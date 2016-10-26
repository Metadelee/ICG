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

    circumference = 2 * 3.1415 * radius;
    area = 3.1415 * radius * radius;

    cout << "\tArea= " << area << "\n" << "\tCircumference= " << circumference << "\n";

    cin.get();
}