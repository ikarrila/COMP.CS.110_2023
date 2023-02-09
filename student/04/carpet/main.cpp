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

using namespace std;

enum Colour {RED, GREEN, BLUE, YELLOW, WHITE, NUMBER_OF_COLORS};
const char CHARACTERS[] = {'R', 'G', 'B', 'Y', 'W'};

vector<vector<Colour>> Board = {};

void initBoard( vector<vector<Colour>>& board, int& x_size, int& y_size, string seed_value="", string input="") {
    default_random_engine rand_gen;

    if( seed_value == "" ) {
        // If the user did not give a seed value,
        // use computer time as the seed value.
        rand_gen.seed( time(NULL) );
    } else {
        // If the user gave a seed value, use it.
        rand_gen.seed( stoi(seed_value) );
    }
    if (input == "") {
        // Filling the board with random numbers between 0 and 4
        // These random numbers correspond to possible colours
        uniform_int_distribution<int> distribution(0, 4);
        for( int y = 0; y < y_size; ++y ) {
            vector< Colour > row;
            for( int x = 0; x < x_size; ++x ) {
                row.push_back( static_cast<Colour>(distribution(rand_gen)) );
            }
            board.push_back( row );
        }
    } else {
        //Filling the board with input string given by user
        string::size_type i = 0;
        for( int y = 0; y < y_size; ++y ) {
            vector< Colour > row;
            for( int x = 0; x < x_size; ++x ) {
                int char_index = distance(CHARACTERS, find(CHARACTERS, CHARACTERS + 5, input[i]));
                row.push_back( static_cast<Colour>(char_index) );
                i++;
            }
            board.push_back( row );
        }
    }
}

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
    }
}

bool isSuitableCarpetString(string input) {
    for (string::size_type i = 0; i < input.length(); i++){
        if (input[i] != 'R' and input[i] != 'G' and input[i] != 'W' and input[i] != 'B' and input[i] != 'Y'){
            cout << "Error: Unknown color." << endl;
            return false;
        }
    }
    return true;
}

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

bool readInitializationInput(string& input, string carpet, string::size_type input_limit, int x, int y) {
    while(true) {
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
            initBoard(Board, x, y, seed);
            return true;
        } else if (input == "i" or input == "I"){

            //if input is correct, create the carpet
            if (readCarpetColours(carpet, input_limit)){
                initBoard(Board, x, y, "", carpet);
                return true;
            }
        }

        // Otherwise input processing continues
    }
}

int main()
{
    int y;
    int x;
    string str = "";
    string carpet = "";
    readSize(x, y);
    readInitializationInput(str, carpet, (x*y), x, y);

    printBoard(Board, std::cout, x, y);

    return EXIT_SUCCESS;
}
