/**
\file 
\brief File contains test functions for Vector class.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

#include "input.hpp"
#include "smart_array.hpp"

using tasks::Vector;

/**
\file 
\brief Prints Vector content.
*/
template <typename T>
void print_vector(const Vector<T> &vec)
{
    const int per_line = 14;
    unsigned size = vec.size();

    for (unsigned i = 0; i < size; ++i) {
        std::cout << vec[i] << (i == 0 || i % per_line ? ' ' : '\n');
    }
    if (size && size % per_line) { std::cout << std::endl; }
}

int *input_arr(int *size_ptr)
{
    *size_ptr = 0;

    while (*size_ptr <= 0) {
        *size_ptr = int_input("Enter size for integer array (> 0): ");
        if (std::cin.eof()) exit(1);
    }
    int *arr = new int [*size_ptr];

    for (int i = 0; i < *size_ptr; ++i) {
        std::cout << i + 1;
        arr[i] = int_input(" Enter integer: ");
    }
    return arr;
}

void test_stl_algorithms_compatibility()
{
    Vector<int> v(5, 5);
    assert(std::count(v.begin(), v.end(), 5) == 5);
    std::cout << "std::count algorithm test successfully passed!\n";
    Vector<int>::iterator it = v.begin();
    std::advance(it, 4);
    assert(v.begin() + 4 == it);
    std::cout << "std::advance algorithm test successfully passed!\n";
}

/**
\file 
\brief Tests creation types of Vector class.
*/
void test_constructor(const int *arr, unsigned arr_size)
{
    Vector<int> vector1;
    assert(0 == vector1.size() && 0 == vector1.capacity() && vector1.empty());
    std::cout << "Test for default constructor of Vector successfully passed!\n";
    Vector<int> vector2(arr_size);
    assert(arr_size == vector2.size() && 0 != vector2.capacity() && !vector2.empty());
    std::cout << "\nTest for constructor of Vector\n"
              << "with elements count and default value successfully passed!\n";
    Vector<int> vector3(arr_size + 3, 3);
    assert(arr_size  + 3 == vector3.size() && 3 == vector3[0]);
    std::cout << "\nTest for constructor of Vector\n"
              << "with elements count and given value successfully passed!\n";
    Vector<int> vector4(vector3);
    assert(vector4.size() == vector3.size() && vector4.capacity() == vector3.capacity());
    assert(vector4 == vector3);
    std::cout << "\nTest for copy constructor of Vector by creating\n"
              << "vector4 from vector3 successfully passed!\n";
    Vector<int> vector5(arr, arr + arr_size);
    assert(arr_size == vector5.size());
    assert(vector5.front() == arr[0] && vector5.back() == arr[arr_size -1]);
    std::cout << "\nTest for constructor of Vector with the contents of the range [first, last)."
              << "\nCreating vector5 with values of given array successfully passed!\n";
    print_vector(vector5); 
}

/**
\file 
\brief Tests iterator usage in Vector class.
*/
void test_iterator(const int * arr, unsigned arr_size)
{
    std::cout << "Creating vector with given array elements.\n"; 
    Vector<int> vector(arr, arr + arr_size);
    Vector<int>::iterator iter = vector.begin();
    Vector<int>::const_iterator iter_end = vector.end();
    std::cout << "Enumerating vector elements using iterators: ";
    for (; iter != iter_end; ++iter) {
        std::cout << *iter << ' ';
    }
    std::cout << "\nEnumerating vector elements using reverse iterators: ";
    Vector<int>::reverse_iterator r_iter = vector.rbegin();
    Vector<int>::const_reverse_iterator r_iter_end = vector.rend();
    for (; r_iter != r_iter_end; ++r_iter) {
        std::cout << *r_iter << ' ';
    }
    std::cout << "\n\nChanging element of vector using const iterator will give compile error.\n"
              << "Uncomment the line 102 in code file to test it.\n";
    Vector<int>::const_iterator const_iter = vector.begin();
    //++*const_iter;
    iter = Vector<int>::iterator(vector.rend());
    std::cout << "\nTesting iterator conversion\nAssigning iterator by vector.rend(), "
              << "*iterator: " << *iter << std::endl;
}

/**
\file 
\brief Tests different ways of accessing Vector elements.
*/
void test_element_access(const std::string* arr, unsigned arr_size)
{
    Vector<std::string> str_vector(arr, arr + arr_size);
    const Vector<std::string> const_str_vector(arr, arr + arr_size);
    
    std::cout << "Creating two vectors, str_vector and const_str_vector, with given array elements.\n"; 
    print_vector(str_vector);
    print_vector(const_str_vector);
    std::cout << "\nAccessing const vector elements by index:\nconst_str_vector[0]: "<< const_str_vector[0]
              << ", const_str_vector[size - 1]: " << const_str_vector[const_str_vector.size() - 1] 
              << "\n\nChanging element of str_vector at index 0, "
              << "str_vector[0] = str_vector[0] + \"_changed\".\n";
    str_vector[0] = str_vector[0] + "_changed";
    std::cout << "str_vector[0]: " << str_vector[0] << std::endl;
    std::cout << "\nChanging element of const_str_vector will give a compile error.\n"
              << "Uncomment the line 130 in code file to test it.\n";
    //const_str_vector[0] = "aaaa"; 
    std::cout << "\nAccessing element by index which is out of range does not raise exception.\n"
              << "const_str_vector[const_str_vector.size()]: " 
              << const_str_vector[const_str_vector.size()] << std::endl;
    std::cout << "\nIterating through str_vector, changing the elements using 'at' function.\n"; 

    for (int i = 0, size = str_vector.size(); i < size; ++i) {
        str_vector.at(i) = str_vector.at(i) + "_changed";
        std::cout << "str_vector.at(" << i << "): " << str_vector.at(i) << std::endl;
    }
    std::cout << "\nTesting 'front' and 'back' member functions.\nstr_vector.front(): " 
              << str_vector.front() << ", str_vector.back(): " << str_vector.back() << std::endl; 
    try {
        std::cout << "\nAccessing element using 'at' with out of range index raises exception.\n";
        std::cout << const_str_vector.at(const_str_vector.size()) << std::endl;
    }
    catch (std::out_of_range &o_f_range) {
        std::cout << "Exception: " << o_f_range.what() << std::endl;
    }
}

/**
\file 
\brief Testing Vector::push_back().
*/
void test_push_back(Vector<int> &vector1, const int *arr, unsigned arr_size)
{
    std::cout << "\n\nPushing given array elements into vector1 from back:\n";
    for (unsigned i = 0; i < arr_size; ++i) {
        vector1.push_back(arr[i]);
        std::cout << "vector1 content: ";
        print_vector(vector1);
    }
}

/**
\file 
\brief Testing Vector::pop_back().
*/
void test_pop_back(Vector<int> &vector1)
{
    int size = vector1.size();

    std::cout << "\nPopping vector1 elements from back:\n";

    for (int i = 0; i < size; ++i) {
        std::cout << "vector1 content: ";
        print_vector(vector1);
        vector1.pop_back();
    }
}

/**
\file 
\brief Inserts value to given Vector object.
*/
void test_insert(Vector<int> &vector1)
{
    std::cout << "\nTesting vector.insert(). ";
    int value = int_input("Enter integer to insert in vector from begin pos: ");
    vector1.insert(vector1.begin(), value);
    std::cout << "vector1 content: ";
    print_vector(vector1);
    value = int_input("Enter integer to insert in vector from end pos: ");
    Vector<int>::iterator iter = vector1.insert(vector1.end(), value);
    std::cout << "vector1 content: ";
    print_vector(vector1);
    std::cout << "Trying inserting value into out of vector range. ";
    value = int_input("Enter integer to insert in vector: ");
    iter += vector1.size();
    vector1.insert(iter, value);
    std::cout << "vector1 content: ";
    print_vector(vector1);

}

/**
\file 
\brief Resizes given Vector object.
*/
void test_resize(Vector<int> &vector1)
{
    std::cout << "\nTesting vector.resize(). ";
    int count = -1;
    while (count <= 0) {
        count = int_input("Enter count of resize tries( may be > 0): ");
        if (std::cin.eof()) exit(1);
    }
    for (int i = 0; i < count; ++i) {
        int value = int_input("Enter new size for vector: ");
        vector1.resize(value);
        std::cout << "vector1 content: ";
        print_vector(vector1);
    }
}

/**
\file 
\brief Removes given Vector elements.
*/
void test_erase(Vector<int> &vector1)
{
    std::cout << "\nTesting vector.erase().\n";
    Vector<int>::iterator iter = vector1.begin();
    std::cout << "Vector before erasing: ";
    print_vector(vector1);
    std::cout << "\nDeleting elements before begin pos: ";
    --iter;
    vector1.erase(iter);
    print_vector(vector1);

    std::cout << "\nDeleting step by step all elements from begin pos: ";
    int size = vector1.size();
    for (int i = 0; i < size; ++i) {
        vector1.erase(vector1.begin());
        print_vector(vector1);
    }
    std::cout << "\nDeleting elements from end pos:\n";
    vector1.erase(vector1.end());
    print_vector(vector1);
}

/**
\file 
\brief Testing assignments of Vector elements.
*/
void test_assigning(Vector<int> &vector1, Vector<int> &vector2)
{
    std::cout << "vector1 and vector2 after assigning vector1 to vector2: \n";
    vector2 = vector1;
    print_vector(vector1);
    print_vector(vector2);
    std::cout << "\nAssigning vector1 by vector1.size * 2 of his first element using vector1.assign()."
              << "\nvector1 content: ";
    vector1.assign(vector1.size() * 2, *vector1.begin());
    print_vector(vector1);
}

/**
\file 
\brief Tests different ways of Vector modification.
*/
void test_modifiers(const int *arr, unsigned arr_size)
{
    Vector<int> vector1;
    Vector<int> vector2(arr, arr + arr_size);

    std::cout << "Creating two vectors, one empty, second with given array elements.\n"; 
    std::cout << "vector1 size: " << vector1.size() << ", capacity: " << vector1.capacity()
              << "\nvector2 size: " << vector2.size() << ", capacity: " << vector2.capacity(); 
    vector1.reserve(arr_size); 
    std::cout << "\n\nCapacity of vector1 after calling vector1.reserve(arr_size): " << vector1.capacity(); 
    test_push_back(vector1, arr, arr_size);
    test_pop_back(vector1);
    test_insert(vector1);
    vector1.clear();
    std::cout << "\nvector1 size after using vector.clear(): " << vector1.size() << std::endl;
    test_resize(vector1);
    std::cout << "\nvector1 and vector2 after swapping:\n";
    vector1.swap(vector2);
    print_vector(vector1);
    print_vector(vector2);
    test_assigning(vector1, vector2);
    test_erase(vector1);
}


/**
\file 
\brief Main test function that calls other tests.
*/
void test_vector()
{

    std::cout << "\n________________Testing compatibility with stl algorithms_________________\n";
    test_stl_algorithms_compatibility();

    std::cout << "\n________________________Testing constructors__________________________\n";
    int size;
    int *arr = input_arr(&size);
    test_constructor(arr, size);

    std::cout << "\n_____________________Testing accessing of elements________________________\n";
    size = 0;

    while (size <= 0) {
        size = int_input("Enter size for string array (> 0): ");
        if (std::cin.eof()) exit(1);
    }
    std::string *string_arr = new std::string [size];

    for (int i = 0; i < size; ++i) {
        std::cout << i + 1;
        string_arr[i] = str_input(" Enter text: ");
    }
    test_element_access(string_arr, size);

    std::cout << "\n__________________________Testing iterators_____ _________________________\n";
    arr = input_arr(&size);
    test_iterator(arr, size);

    std::cout << "\n_______________________Testing vector modifiers_________________________\n";
    test_modifiers(arr, size);
}
