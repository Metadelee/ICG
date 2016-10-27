//--------------------------------------------------------------------------------------
//
// Subject		: Computer Graphics
// Project		: Sheet 1 : Exercise 1 Circle calculation
// Authors		: Lina Ouro,  Leti Parcalabescu, Anushalakshmi Manila
// Date		: Oct  26, 2016
// Description	: Compute the area and circumference of a circle with given radius
//
//--------------------------------------------------------------------------------------

#include <iostream>
//#include<math.h>

int main()
{
    float r, A, circumference;
    std::cout << "Calculating area and circumference of a circle\n";
    std::cout << "Enter the value of radius ...";
    std::cin >> r;
    
    A = 3.1415 * r * r;
    //A = 3.1415 * pow(r,r);
    circumference = 2 * 3.1415 * r;
    
    std::cout << "Area of the circle with radius " << r << " = " << A << std::endl;
    std::cout << "Circumference of the circle with radius " << r << " = " << circumference<< std::endl;
    return 0;
}
