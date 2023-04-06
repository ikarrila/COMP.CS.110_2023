#include "university.hh"
#include <iostream>
#include <memory>

University::University(const std::string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}

University::~University()
{
    for ( auto course : courses_ )
    {
        delete course.second;
    }

    for ( auto account : accounts_ )
    {
        delete account.second;
    }
}

void University::new_course(Params params)
{
    std::string code = params.at(0);
    std::string name = params.at(1);
    if ( courses_.find(code) != courses_.end() )
    {
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    }
    else
    {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ )
    {
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    std::string code = params.at(0);
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }

    courses_.at(code)->print_long_info();
}

void University::new_account(Params params)
{
    std::string full_name = params.at(0);
    int num = 0;
    for ( std::map<int, Account*>::iterator iter = accounts_.begin();
          iter != accounts_.end();
          ++iter )
    {
        if ( iter->second->get_full_name() == full_name )
        {
            std::string email = iter->second->get_email();
            num = Utils::numeric_part(email);
            if(num == 0)
            {
                ++num;
            }
            ++num;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(full_name, account_number, num,
                                     email_suffix_);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

void University::print_account(Params params)
{
    int account = std::stoi(params.at(0));
    std::map<int, Account*>::iterator iter = accounts_.find(account);
    if ( iter == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    courses_.at(code)->add_staff(accounts_.at(account));
}

void University::sign_up(Params params)
{
    // Extracting parameters (course code and student id)
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));

    // Check if course and student exist, and student
    //has not yet graduated.
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    if ( accounts_.at(account)->get_graduation_status() )
    {
        std::cout << ALREADY_GRADUATED << std::endl;
        return;
    }
    // Add the account to the course
    courses_.at(code)->add_student(accounts_.at(account));
}

void University::complete(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    // Completing the course for the student
    accounts_.at(account)->complete_course(courses_.at(code));
}

void University::print_signups(Params params)
{
    std::string code = params.at(0);
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    // Print the list of students who have signed up for the course
    for ( const auto& account : courses_.at(code)->get_course_students()){
        account->print();
    }
}

void University::print_completed(Params params)
{
    int account = std::stoi(params.at(0));
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    int credits = 0;
    for (const auto& course : accounts_.at(account)->get_completed_courses()) {
        std::shared_ptr<Course> course_ptr = std::make_shared<Course>(*course);
        course_ptr->print_info(true);
        credits += course_ptr->get_credits();
    }
    std::cout << "Total credits: " << credits << std::endl;
}

void University::print_study_state(Params params)
{
    int account = std::stoi(params.at(0));
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    std::cout << "Current:" << std::endl;
    for (const auto& course : accounts_.at(account)->get_signed_courses()) {
        course->print_info(true);
    }
    std::cout << "Completed:" << std::endl;

    // Create a shared_ptr to manage the lifetime of the course
    std::vector<std::shared_ptr<Course>> completed_courses = accounts_.at(account)->
            get_completed_courses();

    int credits = 0;
    // Printing all completed courses and adding their credits together
    for (const auto& course : completed_courses) {
        course->print_info(true);
        credits += course->get_credits();
    }
    std::cout << "Total credits: " << credits << std::endl;
}


void University::graduate(Params params)
{
    // Extract student ID and check if the account exists in the system
    int account = std::stoi(params.at(0));
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    // Graduate method completes all courses and blocks further
    //signups for the account
    accounts_.at(account)->graduate();
}
