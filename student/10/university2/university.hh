/* Class: University
 * -----------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -----------------
 * Class representing a simple university with students, staff and courses.
 *
 * Note: Students shouldn't need to make changes to the existing functions
 * or their implementations.
 * */
#ifndef UNIVERSITY_HH
#define UNIVERSITY_HH

#include "account.hh"
#include "course.hh"
#include "utils.hh"
#include <map>
#include <string>

const std::string ALREADY_EXISTS = "Error: Already exists.";
const std::string ALREADY_GRADUATED = "Error: Student already graduated.";
const std::string CANT_FIND = "Error: Can't find anything that matches the given string: ";
const std::string NEW_ACCOUNT = "A new account has been created.";
const std::string NEW_COURSE = "A new course has been created.";

using Params = const std::vector<std::string>&;

using Courses = std::map<std::string, Course*>; // <course_code, Course*>
using Accounts = std::map<int, Account*>;  // <account_number, Account*>

class University
{
public:
    /**
     * @brief University constructor
     * @param email_suffix e.g. "tuni.fi"
     */
    University(const std::string& email_suffix);

    /**
     * @brief University destructor
     */
    ~University();

    /**
     * @brief new_course
     * @param params: course code, name
     * Adds a new course to the system.
     * If course with given code is found from the system, gives an error.
     */
    void new_course(Params params);

    /**
     * @brief print_courses
     * Prints short info of all courses in the system.
     */
    void print_courses(Params);

    /**
     * @brief print_course
     * @param params: course code
     * Prints longer info of given course.
     * If no course with given code is found, gives an error.
     */
    void print_course(Params params);

    /**
     * @brief new_account
     * @param params: full name
     * Adds a new account to the system.
     * If there's an account in the system with the same full name,
     * a different e-mail address is generated.
     */
    void new_account(Params params);

    /**
     * @brief print_accounts
     * Print all accounts found in the system.
     */
    void print_accounts(Params);

    /**
     * @brief print_account
     * @param params: account number
     * Print single account's info
     * If account is not found from the system, gives an error.
     */
    void print_account(Params params);

    /**
     * @brief add_staff
     * @param params: course code, account number
     * Add staff to the course.
     * If course or account is not found, gives an error.
     */
    void add_staff(Params params);

    /**
     * @brief sign_up
     * @param params: course code, account number
     * Signs up the account on course.
     * If any of the parameters is not found, gives an error.
     */
    void sign_up(Params params);

    /**
     * @brief complete_course
     * @param params: course code, account number
     * Complete the course student has previously signed up on.
     * If any of the parameters is not found, gives an error.
     */
    void complete(Params params);

    /**
     * @brief print_signups
     * @param params: course code
     * Print current signups on a course.
     * If course is not found, gives an error.
     */
    void print_signups(Params params);

    /**
     * @brief print_completed
     * @param params: account number
     * Prints completed courses and total credits of the student.
     * If no account is found, gives an error.
     */
    void print_completed(Params params);

    /**
     * @brief print_study_state
     * @param params: account number
     * Print student's all signups, completed courses and total credits.
     * If no account is found, gives an error.
     */
    void print_study_state(Params params);

    /**
     * @brief graduate
     * @param params: account number
     * Completes all courses account has signed up.
     * After graduation account cannot sign up for any course.
     * If no account is found, gives an error.
     */
    void graduate(Params params);

private:
    Courses courses_; // all courses: map<Course code, Course*>
    Accounts accounts_; // all accounts: map<Account number, Account*>

    // Keeps track of the next account id to be given
    int running_number_;

    std::string email_suffix_;
};

#endif // UNIVERSITY_HH


