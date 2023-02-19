#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

int main()
{
    string input_file = "";
    map<string, set<unsigned>> lines_by_word;

    cout << "Input file: ";
    getline(cin, input_file);

    ifstream file_object(input_file);
    if( not file_object ){
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        int row_number = 1;
        string line;
        while( getline(file_object, line) ){
            string word;

            istringstream line_object(line);
            while (line_object >> word) {
                lines_by_word.try_emplace({word, {}});
                lines_by_word.at(word).insert(row_number);
            }
            row_number += 1;
        }
        file_object.close();

        for (const pair<string, set<unsigned>>& pair :lines_by_word) {
            const string& word = pair.first;
            const set<unsigned>& linenumbers = pair.second;

            std::cout << word << " " << linenumbers.size() << ": ";

            const auto last_item_it = --linenumbers.cend();
            for (auto it = linenumbers.cbegin(); it != linenumbers.cend(); ++it) {

                std::cout << *it;
                if (it != last_item_it) {
                    std::cout << ", ";
                }
            }

            std::cout << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
