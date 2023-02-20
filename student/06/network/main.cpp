#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void printNames(const std::map<std::string, std::vector<std::string>>& names, const std::string& id, unsigned depth = 0) {
    std::cout << std::string(depth * 2, '.') << id << std::endl;
    for (const auto& underling : names.at(id)) {
        printNames(names, underling, depth + 1);
    }
}

unsigned depth(const std::map<std::string, std::vector<std::string>>& names, const std::string& id) {
    unsigned deepestPoint = 0;
    for ( const auto& under : names.at(id)) {
        deepestPoint = std::max(deepestPoint, depth(names, under));
    }
    return 1 + deepestPoint;
}

unsigned count(const std::map<std::string, std::vector<std::string>>& names, const std::string& id) {
    const auto& under = names.at(id);
    unsigned underlings_count = under.size();
    for (const auto& underling : under) {
        underlings_count += count(names, underling);
    }
    return underlings_count;
}

int main()
{
    std::map<std::string, std::vector<std::string>> names;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            if (names.find(id1) == names.end()) {
                names[id1] = {};
            }
            names.at(id1).push_back(id2);
            assert(names.count(id2) == 0);
            names[id2] = {};

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::map<std::string, std::vector<std::string>>::iterator i;
            printNames(names, id);
        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            std::cout << count(names, id) << std::endl;
        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            std::cout << depth(names, id) << std::endl;
        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
