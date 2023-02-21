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

std::map<std::string, Book> books;

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
