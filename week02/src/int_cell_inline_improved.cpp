/**
 * A class for simulating an integer memory cell.
 */
class IntCell
{
    public:
    /**
     * Construct the IntCell.
     * Initial value is 0.
     */
    explicit IntCell(int initialValue = 0) : storedValue{ initialValue }
    {
        /*
         * Intentionally empty; uses initialization list
         * for member initialization.
         */
    }

    /**
     * Return the stored value.
     */
    int read() const
    {
        return storedValue;
    }

    /**
     * Change the stored value to x.
     */
    void write(int x) 
    {
        storedValue = x;
    }

    private:
    int storedValue;
};
