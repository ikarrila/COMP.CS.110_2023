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
    if (amount <= saldo_) {
        saldo_ = saldo_ - amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << saldo_ << " euros" << std::endl;
    } else if ( has_credit_ == true and ((saldo_ + credit_limit_) >= amount) ){
        saldo_ -= amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << saldo_ << " euros" << std::endl;
    } else if ( has_credit_ == true and ((saldo_ + credit_limit_) < amount) ){
        std::cout << "Cannot take money: credit limit overflow" << std::endl;
    }else {
        std::cout << "Cannot take money: balance underflow" << std::endl;
    }
}

void Account::set_credit_limit(int credit_limit)
{
    if (has_credit_ == true){
        credit_limit_ = credit_limit;
    } else {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::transfer_to(Account& destination, int amount){
    if ( saldo_ >= amount ){
        saldo_ -= amount;
        destination.saldo_ += amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << saldo_ << " euros" << std::endl;
    } else if ( has_credit_ == true and ((saldo_ + credit_limit_) >= amount) ){
        saldo_ -= amount;
        destination.saldo_ += amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << saldo_ << " euros" << std::endl;
    } else if ( has_credit_ == true and ((saldo_ + credit_limit_) < amount) ){
        std::cout << "Cannot take money: credit limit overflow" << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    } else {
        std::cout << "Cannot take money: balance underflow" << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    }

}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << saldo_ << std::endl;
}
