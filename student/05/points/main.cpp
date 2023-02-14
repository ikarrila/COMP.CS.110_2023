#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

int main()
{
    string input_file = "";
    map<string, int> scoreboard;

    cout << "Input file: ";
    getline(cin, input_file);

    ifstream file_object(input_file);
    if( not file_object ){
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        int row_number = 1;
        string line;
        cout << "Final scores:" << endl;
        while( getline(file_object, line) ){
            string name = line.substr(0, line.find(":"));
            string score = line.substr(line.find(":")+1, line.back());
            if (scoreboard.find(name) != scoreboard.end()){
                scoreboard.at(name) += stoi(score);
            } else {
                scoreboard.insert({name, stoi(score)});
            }
            row_number += 1;
        }
        file_object.close();

        for (auto dataPair : scoreboard){
            cout << dataPair.first << ":" << dataPair.second << endl;
        }
    }
    return EXIT_SUCCESS;
}
