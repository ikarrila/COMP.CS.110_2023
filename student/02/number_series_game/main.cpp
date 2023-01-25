#include <iostream>


int main()
{
    int i = 0;
    int amount;

    std::cout << "How many numbers would you like to have? ";
    std::cin >> amount;
    // Write your code here
    while ( i <= amount ){
        std::cout << i << std::endl;
        ++i;
    }

    return 0;
}
