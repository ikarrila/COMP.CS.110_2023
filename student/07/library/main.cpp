/* Library
 *
 * Desc:
 *   This program implements a library book catalogue datastructure and
 * a UI to go with it. The program reads library data from an csv file
 * appending it into a data structure from which the data can be printed.
 *   Each row of data in the csv format has 4 slots for data, none of which
 * can be empty. The first is library name, second the author, third book name
 * and the fourth describes how many people are waiting for the book or if it
 * is already available on the shelf.
 *   At first, the program asks for an input file from the user. The file is read
 * directly from the build folder. If it cannot be read, an error appears and the
 * program terminates immediately. In case the file is found, it is checked for
 * correct formatting and data is read to a data structure.
 *   Once the data structure has been initialized, certain commands can be used to
 * search information from it. E.g. books in a certain library, books by author,
 * reservations for a book, and which books are loanable. Commands can be inputted
 * as long until the user quits by typing "quit".
 *
 * Name: Iivari Karrila
 * Student number: K437292
 * UserID: gdiika
 * E-Mail: iivari.karrila@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 *
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>

struct Book {
    std::string author;
    std::string title;
    int reservations;
};

using namespace std;

void material(const std::string& library, std::map<std::string, std::vector<Book>>& books) {
    if (books.find(library) == books.end()){
        std::cout << "Error: unknown library" << std::endl;
    } else {
        std::vector<Book>& library_books = books[library];
        std::sort(library_books.begin(), library_books.end(), [](const Book& a, const Book& b) {
            return a.author < b.author;
        });
        for (const auto& book : library_books) {
            std::cout << book.author << ": " << book.title << std::endl;
        }
    }
}

int main(){
    std::map<std::string, std::vector<Book>> books;
    std::string input_file = "";

    std::cout << "Input file: ";
    getline(cin, input_file);

    ifstream file_object(input_file);
    if( not file_object ){
        std::cout << "Error: input file cannot be opened" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::string line = "";
        while(getline(file_object, line)){
            std::istringstream ss(line);
            string library = "";
            string author = "";
            string title = "";
            string status = "";
            int reservations = 0;

            getline(ss, library, ';');
            getline(ss, author, ';');
            getline(ss, title, ';');
            getline(ss, status, ';');

            if (library.empty() or title.empty() or author.empty() or status.empty()){
                std::cout << "Error: empty field" << std::endl;
                return EXIT_FAILURE;
            }

            if (status != "on-the-shelf"){
                reservations = stoi(status);
            }
            Book book;
            book.author = author;
            book.title = title;
            book.reservations = reservations;
            books[library].push_back(book);
        }
        file_object.close();

        std::string input = "";
        while(input != "quit"){
            cout << "lib> ";
            getline(cin, input);

            std::string command = input.substr(0, input.find(" "));
            std::string target_library = "";

            if (command == "libraries"){
                for (auto element : books){
                    std::cout << element.first << std::endl;
                }
            } else if (command == "material"){
                target_library = input.substr(input.find(" ") + 1);

                if (target_library.empty()){
                    std::cout << "Error: wrong number of parameters" << std::endl;
                } else {
                    material(target_library, books);
                }
            } else if (command == "books"){

            } else if (command == "reservable"){

            } else if (command == "loanable"){

            } else {
                std::cout << "Error: unknown command" << std::endl;
            }
        }
    }
    return EXIT_SUCCESS;
}
