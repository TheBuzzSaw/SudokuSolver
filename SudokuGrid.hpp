#ifndef SUDOKUGRID_HPP
#define SUDOKUGRID_HPP

#include <bitset>
#include <iostream>

class SudokuGrid
{
    public:
        SudokuGrid();
        SudokuGrid(const SudokuGrid&) = default;
        ~SudokuGrid() = default;

        SudokuGrid& operator=(const SudokuGrid&) = default;

        void Write(std::ostream& stream) const;
    protected:
    private:
        std::bitset<9 * 9 * 9> _banned;
};

#endif
