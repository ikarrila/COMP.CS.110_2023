#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string input_file = "";
    string output_file = "";

    cout << "Input file: ";
    getline(cin, input_file);
    cout << "Output file: ";
    getline(cin, output_file);

    ofstream output;
    ifstream file_object(input_file);
    if( not file_object ){
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        output.open (output_file);
        int row_number = 1;
        string line;
        while( getline(file_object, line) ){
            output << row_number << " " << line << endl;
            row_number += 1;
        }
        file_object.close();
        output.close();
    }
    return EXIT_SUCCESS;
}
