/**
\file 
\brief Header file containing includes and input functions prototypes. 
*/

#ifndef _STR_INPUT_
#define _STR_INPUT_

#include <iostream>
#include <string>
#include <limits>

bool non(const std::string &);
std::string str_input(const char *, int = 1, bool (*)(const std::string &) = non);
int int_input(const char *);

#endif
