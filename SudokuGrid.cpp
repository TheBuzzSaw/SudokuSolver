#include "SudokuGrid.hpp"
#include <cstdint>

template<typename T>
constexpr bool IsBetween(T value, T low, T high)
{
    return low <= value && value <= high;
}

SudokuGrid::SudokuGrid()
{
}

void SudokuGrid::Write(std::ostream& stream) const
{
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            char value = 'x';
            int index = r * 81 + c * 9;

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
                        value = '?';
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
