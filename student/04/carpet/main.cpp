/* Mystery carpet
 *
 * Desc:
 *   This program implements a mystery carpet applying pattern matching.
 * The carpet consists of squares of different colors, which also holds
 * true for the pattern, but the size of the pattern is always 2 x 2, i.e.
 * it has four colored squares. The program searches for pattern
 * occurrences from the carpet.
 *   At first, the program asks for the size of the carpet (width and heigth).
 * The user is also asked for if the carpet (grid) will be filled with
 * randomly drawn colors, or with user-given ones. In the first option,
 * a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input as many colors as the
 * there are squares in the carpet, whereupon the user lists the first
 * letters of the colors as one long string.
 *   On each round, the user is asked for a pattern to be searched for
 * (a string consisting of four letters/colors). The program prints, how
 * many occurrences was found and from which coordinates they were found.
 *   The program checks if the user-given colors are among accepted ones.
 * The program terminates when the user gives a quitting command ('q' or 'Q').
 *
 * Name: Iivari Karrila
 * Student number: K437292
 * UserID: gdiika
 * E-Mail: iivari.karrila@tuni.fi
 * */
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

enum Colour {RED, GREEN, BLUE, YELLOW, WHITE, NUMBER_OF_COLORS};
const char CHARACTERS[] = {'R', 'G', 'B', 'Y', 'W'};
const int SEACH_SIZE_LIMIT = 4;

vector<vector<Colour>> Carpet = {};

//Function to create a carpet as a 2D vector of Colours.
//2d vector filled either randomly, or from a user input.
void initBoard( vector<vector<Colour>>& board, int& x_size, int& y_size, string seed_value="", string input="") {
    default_random_engine rand_gen;

    if(seed_value == "") {
        // If the user did not give a seed value,
        // use computer time as the seed value.
        rand_gen.seed(time(NULL));
    } else {
        // If the user gave a seed value, use it.
        rand_gen.seed( stoi(seed_value) );
    }
    if (input == "") {
        // Filling the board with random numbers between 0 and 4
        // These random numbers correspond to possible colours
        uniform_int_distribution<int> distribution(0, 4);
        for(int y = 0; y < y_size; ++y) {
            vector< Colour > row;
            for( int x = 0; x < x_size; ++x ) {
                row.push_back( static_cast<Colour>(distribution(rand_gen)) );
            }
            board.push_back(row);
        }
    } else {
        //Filling the board with input string given by user
        string::size_type i = 0;
        for(int y = 0; y < y_size; ++y) {
            vector< Colour > row;
            for( int x = 0; x < x_size; ++x ) {
                int char_index = distance(CHARACTERS, find(CHARACTERS, CHARACTERS + 5, input[i]));
                row.push_back( static_cast<Colour>(char_index) );
                i++;
            }
            board.push_back(row);
        }
    }
}

//Function to show the previously initialized carpet as printed 2D vector.
void printBoard( const vector<vector<Colour>>& board, std::ostream& stream, int& x_size, int& y_size ) {
    // Printing space after each character to make ASCII graphics clearer.
    for( int y = 0; y < y_size; ++y ) {
        for( int x = 0; x < x_size; ++x ) {
            stream << CHARACTERS[board.at(y).at(x)];
            stream << " ";
        }
        stream << endl;
    }
}

//A function to ask for the X and Y size of the carpet.
//These will be given for the InitBoard -function as parametres.
bool readSize(int& x, int& y) {
    while(true) {
        cout << "Enter carpet's width and height: ";

        // If input reading fails (by Control-C), program terminates
        if(not(cin >> x and cin >> y)) {
            return false;
        }

        // If valid coordinates can be read, program execution continues
        if(x >= 2 and y >= 2) {
            return true;
        }

        // Otherwise input processing continues
        cout << "Error: Carpet cannot be smaller than pattern." << endl;
        return false;
    }
}

//Function checks if the given user input contains only colours we can use.
bool isSuitableCarpetString(string& input) {
    for (string::size_type i = 0; i < input.length(); i++){
        input[i] = toupper(input[i]);
        if (input[i] != 'R' && input[i] != 'G' && input[i] != 'W' && input[i] != 'B' && input[i] != 'Y'){
            cout << "Error: Unknown color." << endl;
            return false;
        }
    }
    return true;
}

//Asking the user to input their own string that we'll use to fill the carpet
bool readCarpetColours(string& input, string::size_type input_limit) {
        cout << "Input: ";

        // If input reading fails (by Control-C), program terminates
        if(not(cin >> input)) {
            return false;
        }

        if(input.length() != input_limit) {
            cout << "Error: Wrong amount of colors." << endl;

        // If valid coordinates can be read, program execution continues
        } else if (isSuitableCarpetString(input)){
            return true;
        }
        return false;
}

//This function is reponsible for asking the user to provide all needed inputs to start Initialization
//There are two main ways: R and I. Random generation and Input by user. Based on these the carpet is
//initialized in a slightly different manner.
bool readInitializationInput(vector<vector<Colour>>& carpet, string carpet_string_by_user, int x, int y) {
    while(true) {
        string input = "";
        cout << "Select start (R for random, I for input): ";

        // If input reading fails (by Control-C), program terminates
        if(not(cin >> input)) {
            return false;
        }

        // If valid coordinates can be read, program execution continues
        if(input == "r" or input == "R") {
            string seed = "";
            cout << "Enter a seed value or an empty line: ";
            cin.ignore();
            getline(cin, seed);
            initBoard(carpet, x, y, seed);
            return true;
        } else if (input == "i" or input == "I"){

            //if input is correct, create the carpet
            if (readCarpetColours(carpet_string_by_user, (x*y))){
                initBoard(carpet, x, y, "", carpet_string_by_user);
                return true;
            }
        }

        // Otherwise input processing returns back to the beginning
    }
}

//Searches for matches from user input that have equivalents within the carpet
//The way this works is that we'll go through the whole carpet line by line and
//find matches from left to right and top to bottom. The first XY is printed when a match is found
void matchFound(const vector<vector<Colour>>& board, string input){
    int count = 0;
    for(string::size_type y = 0; y < board.size()-1; y++){
        for(string::size_type x = 0; x < board[0].size()-1; x++){
            if (CHARACTERS[board[y][x]] == input[0] && CHARACTERS[board[y][x+1]] == input[1] &&
                    CHARACTERS[board[y+1][x+1]] == input[3] && CHARACTERS[board[y+1][x]] == input[2]){
                cout << " - Found at (" << int(x+1) << ", " << int(y+1) << ")" << endl;
                count++;
                //Jumping out of the loop with 2x2 fields to avoid double count
                if (board.size() == 2 && board[0].size() == 2){
                    continue;
                }
            }
        }
    }
    cout << " = Matches found: " << count << endl;
}

//Asking the user the give 4-long carpet patch we'll be searching for.
//Same checks as before with the "input custom carpet".
void readStringToSearch(const vector<vector<Colour>>& board){
    string input = "";
    while(true) {
        cout << "Enter 4 colors, or q to quit: ";
        if(not(cin >> input)) {
            continue;
        } else if (input == "Q" or input == "q"){
            break;
        } else if(input.length() != SEACH_SIZE_LIMIT) {
            cout << "Error: Wrong amount of colors." << endl;
            continue;
        // If valid coordinates can be read, program execution continues
        } else if (isSuitableCarpetString(input)){
            matchFound(board, input);
        }
        // Otherwise input processing continues
    }
}

int main()
{
    int y = 0;
    int x = 0;
    string carpet = "";
    if (not readSize(x, y)){
        return EXIT_FAILURE;
    }
    readInitializationInput(Carpet, carpet, x, y);
    printBoard(Carpet, std::cout, x, y);
    readStringToSearch(Carpet);

    return EXIT_SUCCESS;
}
