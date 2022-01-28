#include "int_cell.h"

/**
 * Construct the IntCell with initialValue
 */
IntCell::IntCell(int initialValue) : storedValue{ initialValue }
{
    /* 
     * Intentionally left blank; use initialization list to 
     * initialize data member.
     */
}

/**
 * Return the stored value.
 */
int IntCell::read() const 
{
    return storedValue;
}

/**
 * Store x.
 */
void IntCell::write(int x) 
{
    storedValue = x;
}
