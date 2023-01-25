#include <iostream>


int main()
{
    int i = 1;
    int amount;

    std::cout << "How many numbers would you like to have? ";
    std::cin >> amount;

    while (i <= amount){
        if ((i % 3 == 0) && (i % 7 == 0)){
            std::cout << "zip boing" << std::endl;
        } else if (i % 3 == 0){
            std::cout << "zip" << std::endl;
        } else if (i % 7 == 0){
            std::cout << "boing" << std::endl;
        } else{
            std::cout << i << std::endl;
        }
        ++i;
    }

    return 0;
}
