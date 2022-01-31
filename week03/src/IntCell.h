#ifndef CSC232_INT_CELL_H__
#define CSC232_INT_CELL_H__

/**
 * A class for simulating an integer memory cell.
 */
class IntCell
{
    public:
    explicit IntCell( int initialValue = 0 );
    int read( ) const;
    void write( int x );

    private:
    int storedValue;
};

#endif // CSC232_INT_CELL_H__
