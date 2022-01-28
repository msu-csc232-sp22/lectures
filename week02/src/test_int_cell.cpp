#include <cstdlib>
#include <iostream>
#include "int_cell.h"

using std::cout;
using std::endl;

int main()
{
    IntCell m;

    m.write(5);
    cout << "Cell contents: " << m.read() << endl;

    return EXIT_SUCCESS;
}


/*
Go over the need for -std=c++11

$ g++ int_cell.cpp test_int_cell.cpp
int_cell.cpp:6:49: error: expected '('
IntCell::IntCell(int initialValue) : storedValue{ initialValue }
                                                ^
int_cell.cpp:6:63: error: expected ';' after expression
IntCell::IntCell(int initialValue) : storedValue{ initialValue }
                                                              ^
                                                              ;
int_cell.cpp:6:51: warning: expression result unused [-Wunused-value]
IntCell::IntCell(int initialValue) : storedValue{ initialValue }
                                                  ^~~~~~~~~~~~
int_cell.cpp:7:1: error: expected unqualified-id
{
^
1 warning and 3 errors generated.
$ g++ -std=c++11 int_cell.cpp test_int_cell.cpp
$ ./a.out
Cell contents: 5
*/