#include <iostream>
#include <cctype>
#include <string>

using namespace std;
std::string az = "abcdefghijklmnopqrstuvwxyz";

int checkWord(std::string input){
    string::size_type len = 0;
    len = input.length();
    for (unsigned long i = 0; i < len; i++){
        if ( input[i] >= 'a' && input[i] <= 'z' ){
            //cout << "Char " << input[i] << " found." << endl;
        } else {
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

int checkChar(std::string input){
    string::size_type len = 0;
    len = input.length();
    for (unsigned long i = 0; i < len; i++){
        if ( input[i] >= 'a' && input[i] <= 'z' ){
            //cout << "Char " << input[i] << " found." << endl;
        } else {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

int findAll(std::string input){
    string::size_type len = 0;
    len = input.length();
    for (unsigned long i = 0; i < len; i++){
        if ( input.find(az[i]) == string::npos ){
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

int encryption(std::string word, std::string key){
    string::size_type len = 0;
    len = word.length();
    string empty = "";
    for (unsigned long i = 0; i < len; i++){
        int index = az.find(word[i]);
        empty.insert(i, 1, key[index]);
    }
    cout << "Encrypted text: " << empty << endl;
    return 0;
}

int main()
{
    string key = "";
    string word = "";

    cout << "Enter the encryption key: ";
    cin >> key;

    //Tarkistaa merkkijonon pituuden
    if ( key.length() != 26 ) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        exit(EXIT_FAILURE);
    }

    //Checks for all letters a-z, only small letters
    checkChar(key);
    findAll(key);

    cout << "Enter the text to be encrypted: ";
    cin >> word;
    checkWord(word);
    encryption(word, key);

    return 0;
}
