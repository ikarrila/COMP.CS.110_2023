#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>

Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number), graduated_(false)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}

Account::~Account()
{
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() const
{
    return email_;
}

std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

bool Account::sign_course(Course* course)
{
    if (graduated_ == true)
    {
        std::cout << "Error: Student already graduated." << std::endl;
        return false;
    }

    // Add course to signed courses and print success message
    signed_courses_.push_back(course);
    std::cout << SIGNED_UP << std::endl;
    return true;
}

bool Account::complete_course(Course* course)
{
    // Check if account has course in signed courses
    bool found = false;
    for (auto it = signed_courses_.begin(); it != signed_courses_.end(); ++it) {
        if (*it == course) {
            signed_courses_.erase(it);
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << NO_SIGNUPS << std::endl;
        return false;
    }

    // Add course to completed courses and print success message
    completed_courses_.push_back(course);
    std::cout << COMPLETED << std::endl;
    return true;
}

const std::vector<Course*>& Account::get_completed_courses() const
{
    return completed_courses_;
}

const std::vector<Course*>& Account::get_signed_courses() const
{
    return signed_courses_;
}

void Account::graduate()
{
    // move all signed courses to completed courses
    for (auto& course : signed_courses_) {
        completed_courses_.push_back(course);
    }
    signed_courses_.clear();

    // mark the account as graduated
    graduated_ = true;
    std::cout << GRADUATED << std::endl;
}

bool Account::get_graduation_status() const
{
    return graduated_;
}
