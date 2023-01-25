#include <iostream>


int main()
{
    int i = 1;
    int amount;

    std::cout << "How many numbers would you like to have? ";
    std::cin >> amount;

    while ( i <= amount ){
        if ( i % 3 == 0 ){
            std::cout << "zip" << std::endl;
        } else{
            std::cout << i << std::endl;
        }
        ++i;
    }

    return 0;
}
