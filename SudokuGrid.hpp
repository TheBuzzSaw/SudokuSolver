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

        bool Set(int row, int column, int value);

        void Write(std::ostream& stream) const;
    protected:
    private:
        std::bitset<9 * 9 * 9> _banned;

        void Ban(int row, int column, int value);
        void SpreadBan(int row, int column, int value);
};

#endif
