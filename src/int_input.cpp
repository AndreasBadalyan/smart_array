/**
\file 
\brief Source file that contains input function.
*/

#include "input.hpp"

/**
Accepts user input and handles invalid cases. 
\param message Text to be displayed.
\return User input as integer.
*/
int int_input(const char *message)
{
    int input;

    while (!std::cin.eof()) {
        std::cout << message; 
        std::cin >> input;

        if (std::cin.good()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        } else {
            std::cout << "Invalid input!" << std::endl;
            std::cin.clear(std::ios::goodbit);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

}
