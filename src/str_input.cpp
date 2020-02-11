/**
\file
\brief Source file containing string input function.
*/

#include "input.hpp"

/**
Accepts and validates user input. 
\param message Text message to display on screan.
\param len Length that must be compared with input string length.
\param f_ptr pointer of function that must apply to input string, 
        by default it's non function that returns true for every case.
\return Input string that is validated.
*/
std::string str_input(const char *message, int len, bool (*f_ptr)(const std::string &))
{
    std::string input;

    while (!std::cin.eof()) {
        std::cout << message;
        std::getline(std::cin, input);

        if (input.length() >= len && (*f_ptr)(input)) {
            return input;
        }
        std::cout << "invalid input!" << std::endl;
    }
    return input;
}

/**
Default function for str_input that returns true for every case.
\param input Input string.
\return Always true.
*/
bool non(const std::string &input)
{
    return true;    
}
