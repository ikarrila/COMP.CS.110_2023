#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int number;
    int cube;
    cout << "Enter a number: " << endl;
    cin >> number;

    cube = pow(number, 3);
    if (cbrt(cube) == number){
        cout << "The cube of " << number << " is " << cube << endl;
    } else {
        cout << "Error! The cube of " << number << " is not " << cube << endl;
    }
    return 0;
}
