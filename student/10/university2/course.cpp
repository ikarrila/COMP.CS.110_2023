#include "course.hh"
#include <iostream>

Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}

Course::~Course()
{
}

void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}

void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}

void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0; i < course_staff_.size(); ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    std::cout << STAFF_ADDED << std::endl;
}

void Course::add_student(Account *new_student)
{
    // Checking if account is already on the course
    for ( unsigned int i = 0; i < course_students_.size(); ++i )
    {
        if ( course_students_.at(i) == new_student )
        {
            std::cout << STUDENT_EXISTS << std::endl;
            return;
        }
    }

    if (new_student->sign_course(this)){
        course_students_.push_back(new_student);
        std::cout << STUDENT_ADDED << std::endl;
    } else {
        //Test print
        std::cout << "FAIL" << std::endl;
    }
}

const std::string Course::get_code() const
{
    return course_code_;
}

int Course::get_credits() const
{
    return credits_;
}




