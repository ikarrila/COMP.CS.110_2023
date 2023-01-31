#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include "date.hh"


class Book
{
public:
    Book();

    Book(std::string name, std::string author, bool loaned = false);

    ~Book();

    void print();
    void loan(Date& day);
    void renew();
    void give_back();
private:
    std::string name_;
    std::string author_;
    bool loaned_;
    Date loanDate_;
    Date returnDate_;
};

#endif // BOOK_HH
