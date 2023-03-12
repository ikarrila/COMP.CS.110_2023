/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 *
 * In the project, this class should be expanded to
 * include necessary methods and attributes.
 * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
//#include <vector>

class Course;

const std::string NO_SIGNUPS = "No signups found on this course.";
const std::string SIGNED_UP = "Signed up on the course.";
const std::string COMPLETED = "Course completed.";
const std::string GRADUATED = "Graduated, all courses completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const std::string& full_name, int account_number, int duplicates,
            const std::string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email() const;

    /**
     * @brief get_full_name
     * @return full name of this account
     */
    std::string get_full_name() const;

    /**
     * @brief get_account_number
     * @return account number linked to this account
     */
    int get_account_number() const;

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;

    // Most probably you will need here an attribute (e.g. vector) containing 
    // courses the account has signed up for (either completed or uncompleted
    // or both)
};

#endif // ACCOUNT_HH


