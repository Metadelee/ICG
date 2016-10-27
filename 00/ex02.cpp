//--------------------------------------------------------------------------------------
//
// Subject		: Computer Graphics
// Project		: Sheet 1 : Exercise 2 Iterative Computation
// Authors		: Lina Ouro,  Leti Parcalabescu, Anushalakshmi Manila
// Date		: Oct  26, 2016
// Description	:
//
//--------------------------------------------------------------------------------------

#include <iostream>

int main()
{
    float f[105] = {0};
    f[0] = 0.5;
    
    std::cout << "Iterative computation for \n";
    for (float a = 2.0; a < 3.9; a += 0.1)
    {
        std::cout << "--------------------------------------\n";
        std::cout << " a = " << a << ":\n" << std::endl;
        
        for (int n = 0; n < 105; n += 1)
        {
            f[n+1] = a * f[n] * ( 1 - f[n]);
            
            while (n > 99 && n < 105)
            {
                if ( n == 100)
                {
                    std::cout << " f[100] = " << f[n] << "\n" ;
                    break;
                }
                
                else if ( n == 101)
                {
                    std::cout << " f[101] = " << f[n] << "\n" ;
                    break;
                }
                
                else if ( n == 102)
                {
                    std::cout << " f[102] = " << f[n] << "\n" ;
                    break;
                }
                else if ( n == 103)
                {
                    std::cout << " f[103] = " << f[n] << "\n" ;
                    break;
                }
                else if ( n == 104)
                {
                    std::cout << " f[104] = " << f[n] << "\n" ;
                    break;
                }
                
            }
            
        }
        
    }
    return 0;
}
