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

struct Book {
    std::string title;
    std::string author;
    std::string status;
};

using namespace std;

int main(){
    std::map<std::string, Book> books;
    std::string input_file = "";

    std::cout << "Input file: ";
    getline(cin, input_file);

    ifstream file_object(input_file);
    if( not file_object ){
        std::cout << "Error: input file cannot be opened" << std::endl;
        return EXIT_FAILURE;
    } else {
        int row_number = 1;
        std::string line = "";
        while( getline(file_object, line) ){
            std::istringstream ss(line);
            string library = "";
            string title = "";
            string author = "";
            string status = "";

            getline(ss, library, ';');
            getline(ss, title, ';');
            getline(ss, author, ';');
            getline(ss, status, ';');

            if (library.empty() or title.empty() or author.empty() or status.empty()){
                std::cout << "Error: empty field" << std::endl;
                return EXIT_FAILURE;
            }

            books[library] = {author, title, status};

            std::cout << books[library].title << std::endl;

            row_number += 1;
        }
        file_object.close();
    }
    return EXIT_SUCCESS;
}
