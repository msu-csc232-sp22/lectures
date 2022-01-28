#include <cstdlib>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> squares( 100 );

    for ( int i = 0; i < squares.size( ); ++i )
    {
        squares[ i ] = i * i;
    }

    for (int i = 0; i < squares.size( ); ++i )
    {
        cout << i << " " << squares[ i ] << endl;
    }

    return EXIT_SUCCESS;
}
