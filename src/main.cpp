
#include <iostream>
#include "foo.hpp"

int main (int argc, char** argv, char** arge)
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << "C++ version: " << __cplusplus << std::endl;
    std::cout << "f(3.4) = " << f(3.4) << std::endl; 
    return EXIT_SUCCESS;
}
