#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// TODO: Implement split function here
// Do not change main function
std::vector< std::string > split(std::string str, char separator, bool skip_empty = false){
    std::stringstream test(str);
    std::string segment;
    std::vector<std::string> result;

    while(std::getline(test, segment, separator)){
        if (not skip_empty){
            result.push_back(segment);
        } else {
            if (segment != ""){
                result.push_back(segment);
            }
        }
    }
    if (str.back() == separator and skip_empty == false){
        result.push_back((""));
    }
    return result;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
