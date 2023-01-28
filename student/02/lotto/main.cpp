#include <iostream>
#include <string>

using namespace std;

unsigned long int factorial(unsigned long int number){
    unsigned long int factorial = 1;
    for(unsigned long int i = 1; i <= number; ++i){
        factorial *= i;
    }
    return factorial;
}

unsigned long int possibilities(unsigned long int n, unsigned long int p){
    return (factorial(n)/(factorial(n-p)*factorial(p)));
}

int main()
{
    long int total = 0;
    long int drawn = 0;

    cout << "Enter the total number of lottery balls: ";
    cin >> total;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn;

    if (total < 0 or drawn < 0){
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    } else if (drawn > total){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;
    } else {
        cout << "The probability of guessing all " << drawn << " balls correctly is 1/" << possibilities(total,drawn) << endl;
    }

    return 0;
}
