#include <cstdlib>
#include <iostream>
#include "IntCell.h"

int main()
{
    IntCell *m;

    m = new IntCell{ 0 };
    m->write( 5 );

    std::cout << "Cell contents: " << m->read( ) << std::endl;

    delete m;
    return EXIT_SUCCESS;
}
