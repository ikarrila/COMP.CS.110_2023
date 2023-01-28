#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int num;
    int factor1;
    int factor2;
    cout << "Enter a positive number: ";

    while (true) {
        cin >> num;
        int factor1 = sqrt(num);
        int factor2 = sqrt(num);
        if (num <= 0){
            cout << "Only positive numbers accepted" << endl;
            return 0;
        } else{
            while (true){
                if (factor1 * factor2 == num){
                   cout << num << " = " << factor1 << " * " << factor2 << endl;
                   return 0;
                } else {
                    if (factor1 * factor2 > num){
                        factor1 = factor1 - 1;
                    } else if (factor1 * factor2 < num){
                        factor2 = factor2 + 1;
                    } else{
                        factor1 = factor1 + 1;
                    }
                }
            }
        }
    }
    if (factor1 > factor2) {
        int temp = factor1;
        factor1 = factor2;
        factor2 = temp;
    }
    cout << num << " = " << factor1 << " * " << factor2 << endl;
    return 0;
}

