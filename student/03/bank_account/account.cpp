#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit, int saldo):
    owner_(owner), has_credit_(has_credit), saldo_(saldo)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::save_money(int amount)
{
    saldo_ = saldo_ + amount;
}

void Account::take_money(int amount)
{
    saldo_ = saldo_ - amount;
}

void Account::set_credit_limit(int credit_limit)
{
    credit_limit_ = credit_limit;
}

void Account::transfer_to(Account &account, int amount)
{
    account.save_money(amount);
    saldo_ = saldo_ - amount;
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << saldo_ << std::endl;
}
