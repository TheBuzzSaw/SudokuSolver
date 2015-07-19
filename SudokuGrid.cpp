#include "SudokuGrid.hpp"
#include <cstdint>

template<typename T>
static constexpr bool IsBetween(T value, T low, T high)
{
    return low <= value && value <= high;
}

static constexpr int IndexOf(int row, int column)
{
    return row * 81 + column * 9;
}

SudokuGrid::SudokuGrid()
{
}

bool SudokuGrid::Set(int row, int column, int value)
{
    int index = IndexOf(row, column);

    if (_banned[index + value])
        return false;

    for (int i = 0; i < 9; ++i)
        _banned[index + i] = i != value;

    SpreadBan(row, column, value);

    return true;
}

void SudokuGrid::Write(std::ostream& stream) const
{
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            int index = IndexOf(r, c);
            char value = 'x';

            for (int i = 0; i < 9; ++i)
            {
                if (!_banned[index + i])
                {
                    if (value == 'x')
                    {
                        value = '1' + i;
                    }
                    else
                    {
                        value = '.';
                        break;
                    }
                }
            }

            stream << value;

            if (c == 2 || c == 5)
                stream << '|';
        }

        stream << '\n';

        if (r == 2 || r == 5)
            stream << "---+---+---\n";
    }
}

void SudokuGrid::Ban(int row, int column, int value)
{
    int index = IndexOf(row, column);

    if (!_banned[index + value])
    {
        _banned[index + value] = true;

        bool found = false;
        int legalValue = -1;

        for (int i = 0; i < 9; ++i)
        {
            if (!_banned[index + i])
            {
                if (found)
                {
                    found = false;
                    break;
                }
                else
                {
                    legalValue = i;
                    found = true;
                }
            }
        }

        if (found) SpreadBan(row, column, legalValue);
    }
}

void SudokuGrid::SpreadBan(int row, int column, int value)
{
    for (int r = 0; r < 9; ++r)
        if (r != row) Ban(r, column, value);

    for (int c = 0; c < 9; ++c)
        if (c != column) Ban(row, c, value);

    int boxRow = (row / 3) * 3;
    int boxColumn = (column / 3) * 3;

    for (int r = 0; r < 3; ++r)
    {
        int rr = boxRow + r;

        for (int c = 0; c < 3; ++c)
        {
            int cc = boxColumn + c;

            if (rr != row && cc != column)
                Ban(rr, cc, value);
        }
    }
}
