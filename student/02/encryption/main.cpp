#include <iostream>

using namespace std;

int main()
{
    string key;
    string allLetters = "abcdefghijklmnopqrstuvwxyz";
    cout << "Enter the encryption key: ";
    cin >> key;

    if (key.length() < 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return 1;
    } else if (key.find_first_not_of(allLetters) ){
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return 1;
    } else{
        for (int i = 0; i < int(key.size()); ++i){
            string::size_type finder = 0;
            finder = key.find(allLetters[i]);
            if ( finder == string::npos){
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
                return 1;
            }
        }
    }
        /*else if (key.find()){
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
    }*/


    return 0;
}
