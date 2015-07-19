#include "SudokuGrid.hpp"
#include <iostream>
using namespace std;

const int TestPuzzle[] = {
    0, 9, 0, 0, 0, 2, 1, 5, 0,
    0, 2, 5, 0, 8, 0, 3, 0, 0,
    4, 3, 7, 1, 0, 5, 0, 0, 0,
    2, 4, 0, 0, 0, 0, 9, 0, 8,
    0, 0, 0, 0, 4, 0, 0, 0, 0,
    5, 0, 9, 0, 0, 0, 0, 1, 7,
    0, 0, 0, 5, 0, 6, 8, 4, 1,
    0, 0, 1, 0, 9, 0, 7, 3, 0,
    0, 8, 4, 2, 0, 0, 0, 9, 0
};

int main(int argc, char** argv)
{
    SudokuGrid grid;

    int index = 0;

    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            auto value = TestPuzzle[index++];

            if (value > 0)
                grid.Set(r, c, value - 1);
        }
    }

    grid.Write(cout);
    return 0;
}
