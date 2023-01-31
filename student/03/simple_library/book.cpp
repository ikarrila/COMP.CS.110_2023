#include "book.hh"
#include "date.hh"
#include <iostream>

Book::Book():
    name_(""), author_("")
{}

Book::~Book()
{
}

Book::Book(std::string name, std::string author, bool loaned):
    name_(name), author_(author), loaned_(loaned)
{
}

void Book::print()
{
    std::cout << name_ << " : " << author_ << std::endl;
    if (loaned_ == false){
        std::cout << "- available" << std::endl;
    } else {
        std::cout << "- loaned: ";
        loanDate_.print();
        std::cout << "- to be returned: ";
        returnDate_.print();
    }
}

void Book::renew()
{
    if (loaned_ == true){
        loanDate_.advance(28);
    } else {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }

}

void Book::loan(Date& day)
{
    if (loaned_ == false){
        loanDate_ = day;
        returnDate_ = day;
        loanDate_.advance(28);
        loaned_ = true;
    } else {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
}

void Book::give_back()
{
    loaned_ = false;
}
