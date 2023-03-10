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
#include <set>

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

void printBooks(const std::string& library, const std::string& author, std::map<std::string, std::vector<Book>>& books){
    if (books.find(library) == books.end()){
        std::cout << "Error: unknown library" << std::endl;
    } else {
        std::vector<Book>& library_books = books[library];
        std::sort(library_books.begin(), library_books.end(), [](const Book& a, const Book& b) {
            return a.title < b.title;
        });
        bool author_exist = false;
        for (const auto& book : library_books) {
            if (book.author == author){
                author_exist = true;
                if (book.reservations == 0){
                    std::cout << book.title << " --- on the shelf" << std::endl;
                } else {
                    std::cout << book.title << " --- " << book.reservations << " reservations" << std::endl;
                }
            }
        }
        if (!author_exist){
            std::cout << "Error: unknown author" << std::endl;
        }
    }
}

void reservable(const std::string& author, const std::string& book_title, std::map<std::string, std::vector<Book>>& books) {
    bool found_book = false;
    int min_reservations = 100;
    std::map<int, std::vector<std::string>> queues; // reservation queues indexed by length

    std::map<std::string, std::map<std::string, Book>> searchList;

    // Loop through each library in the books map
    for (auto& library : books) {
        // Initialize a new map for the current library in the libraries map
        std::map<std::string, Book> booksInLibrary;
        // Loop through each book in the current library in the books map
        for (auto& book : library.second) {
            // Add the book to the booksInLibrary map with the book's name as the key
            booksInLibrary[book.title] = book;
        }
        // Add the booksInLibrary map to the libraries map with the library's name as the key
        searchList[library.first] = booksInLibrary;
    }


    // Search for the book in the libraries
    for (auto& [library_name, books] : searchList) {
        for (auto& [title, book] : books) {
            if (book.author == author && title == book_title) {
                found_book = true;

                if (book.reservations >= 100) {
                    std::cout << "Book is not reservable from any library" << std::endl;
                    return;
                }

                if (book.reservations == 0) {
                    std::cout << "on the shelf" << std::endl;
                    std::cout << "--- " << library_name << std::endl;
                    return;
                }
                if (book.reservations < min_reservations){
                    min_reservations = book.reservations;
                }
                queues[book.reservations].push_back(library_name);
            }
        }
    }

    if (!found_book) {
        std::cout << "Book is not a library book" << std::endl;
        return;
    }

    // Find the shortest reservation queue
    if (!queues.empty()) {
        auto shortest_queue = queues.begin()->second;
        std::cout << min_reservations << " reservations" << std::endl;
        for (auto& library_name : shortest_queue) {
            std::cout << "--- " << library_name << std::endl;
        }
    } else {
        std::cout << "Error: no reservation queues found" << std::endl;
    }
}

void loanable(std::map<std::string, std::vector<Book>>& books) {
    std::set<std::string> seen_books; // To keep track of already seen books
    std::vector<std::string> loanable_books;

    // Loop through each library in the books map
    for (auto& library : books) {
        // Loop through each book in the current library in the books map
        for (auto& book : library.second) {
            if (book.reservations == 0 && seen_books.find(book.author + " " + book.title) == seen_books.end()) {
                seen_books.insert(book.author + " " + book.title);
                loanable_books.push_back(book.author + ": " + book.title);
            }
        }
    }

    // Sort the loanable books in alphabetical order based on author and title
    std::sort(loanable_books.begin(), loanable_books.end());

    // Print the loanable books
    for (auto& book : loanable_books) {
        std::cout << book << std::endl;
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
            std::string target_author = "";
            std::string target_title = "";

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
                std::istringstream ss(input);
                string com = "";
                getline(ss, com, ' ');
                getline(ss, target_library, ' ');
                getline(ss, target_author, '\n');

                if (target_library.empty() or target_author.empty()){
                    std::cout << "Error: wrong number of parameters" << std::endl;
                } else {
                    printBooks(target_library, target_author, books);
                }
            } else if (command == "reservable"){

                std::istringstream ss(input);
                string com = "";
                getline(ss, com, ' ');
                getline(ss, target_author, ' ');
                getline(ss, target_title, '\n');

                target_title.erase(
                    std::remove(target_title.begin(), target_title.end(), '\"'),
                    target_title.end());

                reservable(target_author, target_title, books);

            } else if (command == "loanable"){
                loanable(books);
            } else if (command == "quit"){
                continue;
            } else {
                std::cout << "Error: unknown command" << std::endl;
            }
        }
    }
    return EXIT_SUCCESS;
}
