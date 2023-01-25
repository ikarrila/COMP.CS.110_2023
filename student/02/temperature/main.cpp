#include <iostream>

using namespace std;

int main()
{
    float temp;
    float celsius;
    float fahrenheit;

    cout << "Enter a temperature: ";
    cin >> temp;

    fahrenheit = (temp * 1.8 + 32);
    celsius = ((temp - 32) / 1.8);

    cout << temp << " degrees Celsius is " << fahrenheit << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << celsius << " degrees Celsius" << endl;

    return 0;
}
