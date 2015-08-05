#ifndef CUSTOMSUDOKUGRID_HPP
#define CUSTOMSUDOKUGRID_HPP

#include "SudokuGrid.hpp"
#include <iomanip>
#include <cstdio>

template<int N> class CustomSudokuGrid
{
    static constexpr auto N2 = N * N;
    static constexpr auto CellCount = N2 * N2;

    static constexpr int IndexOf(int row, int column) noexcept
    {
        return row * N2 * N2 + column * N2;
    }

    std::bitset<CellCount * N2> _banned;

    void Ban(int row, int column, int value) noexcept;
    void SpreadBan(int row, int column, int value) noexcept;
    int CountLegalValues(int index) const noexcept;

public:
    constexpr CustomSudokuGrid() noexcept = default;
    constexpr CustomSudokuGrid(const CustomSudokuGrid&) noexcept = default;
    ~CustomSudokuGrid() noexcept = default;

    CustomSudokuGrid& operator=(const CustomSudokuGrid&) noexcept = default;

    bool Set(int row, int column, int value) noexcept;
    //bool Solve() noexcept;

    bool IsSolved() const noexcept;
    bool CanBeSolved() const noexcept;
    int Value(int row, int column) const noexcept;

    std::ostream& Write(std::ostream& stream) const;
};

template<int N>
bool CustomSudokuGrid<N>::Set(int row, int column, int value) noexcept
{
    int index = IndexOf(row, column);
    if (_banned.test(index + value)) return false;
    for (int i = 0; i < N2; ++i) _banned.set(index + i, i != value);
    SpreadBan(row, column, value);
    return true;
}

template<int N>
bool CustomSudokuGrid<N>::IsSolved() const noexcept
{
    for (int i = 0; i < CellCount; i += N2)
        if (CountLegalValues(i) != 1) return false;

    return true;
}

template<int N>
bool CustomSudokuGrid<N>::CanBeSolved() const noexcept
{
    for (int i = 0; i < CellCount; i += N2)
        if (CountLegalValues(i) == 0) return false;

    return true;
}

template<int N>
int CustomSudokuGrid<N>::Value(int row, int column) const noexcept
{
    int index = IndexOf(row, column);
    int result = NoValues;

    for (int i = 0; i < N2; ++i)
    {
        if (!_banned.test[index + i])
        {
            if (result == NoValues)
                result = i;
            else
                return MultipleValues;
        }
    }

    return result;
}

template<int N>
void CustomSudokuGrid<N>::Ban(int row, int column, int value) noexcept
{
    int index = IndexOf(row, column);
    if (_banned.test(index + value)) return;
    _banned.set(index + value);

    bool found = false;
    int legalValue = -1;

    for (int i = 0; i < N2; ++i)
    {
        if (!_banned.test(index + i))
        {
            if (found)
            {
                // Multiple legal values.
                return;
            }
            else
            {
                legalValue = i;
                found = true;
            }
        }
    }

    // Only spread the ban if one legal value remains.
    if (found) SpreadBan(row, column, legalValue);
}

template<int N>
void CustomSudokuGrid<N>::SpreadBan(int row, int column, int value) noexcept
{
    for (int r = 0; r < N2; ++r)
        if (r != row) Ban(r, column, value);

    for (int c = 0; c < N2; ++c)
        if (c != column) Ban(row, c, value);

    int boxRow = (row / N) * N;
    int boxColumn = (column / N) * N;

    for (int r = 0; r < N; ++r)
    {
        int rr = boxRow + r;
        if (rr == row) continue;

        for (int c = 0; c < N; ++c)
        {
            int cc = boxColumn + c;
            if (cc == column) continue;

            Ban(rr, cc, value);
        }
    }
}

template<int N>
int CustomSudokuGrid<N>::CountLegalValues(int index) const noexcept
{
    int result = 0;
    for (int i = 0; i < N2; ++i) result += !_banned.test(index + i);
    return result;
}

template<int N>
std::ostream& CustomSudokuGrid<N>::Write(std::ostream& stream) const
{
    for (int r = 0; r < N2; ++r)
    {
        for (int c = 0; c < N2; ++c)
        {
            int index = IndexOf(r, c);
            int value = NoValues;

            for (int i = 0; i < N2; ++i)
            {
                if (!_banned.test(index + i))
                {
                    if (value == NoValues)
                    {
                        value = i;
                    }
                    else
                    {
                        value = MultipleValues;
                        break;
                    }
                }
            }

            stream << std::setw(3) << std::right;

            if (value == NoValues)
                stream << 'x';
            else if (value == MultipleValues)
                stream << '.';
            else
                stream << (value + 1);
        }
    }
}

template<int N>
std::ostream& operator<<(std::ostream& stream, const CustomSudokuGrid<N>& grid)
{
    return grid.Write(stream);
}

#endif
