#include "SudokuGrid.hpp"
#include <iostream>
#include <fstream>
using namespace std;

// http://www.websudoku.com/?level=1&set_id=632927121
const int EasyTestPuzzle[] = {
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

// http://www.websudoku.com/?level=4&set_id=8020976223
const int EvilTestPuzzle[] = {
    3, 5, 9, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 7, 0, 5, 0, 1, 8,
    0, 0, 0, 0, 9, 0, 0, 0, 0,
    0, 8, 0, 9, 0, 0, 5, 0, 0,
    2, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 3, 0, 0, 6, 0, 2, 0,
    0, 0, 0, 0, 2, 0, 0, 0, 0,
    8, 4, 0, 1, 0, 3, 0, 0, 0,
    0, 0, 0, 6, 0, 0, 4, 7, 3,
};

// http://devcry.heiho.net/2015/07/solving-mother-of-all-sudoku-puzzles.html
const int MotherTestPuzzle[] = {
    0, 0, 5, 3, 0, 0, 0, 0, 0,
    8, 0, 0, 0, 0, 0, 0, 2, 0,
    0, 7, 0, 0, 1, 0, 5, 0, 0,
    4, 0, 0, 0, 0, 5, 3, 0, 0,
    0, 1, 0, 0, 7, 0, 0, 0, 6,
    0, 0, 3, 2, 0, 0, 0, 8, 0,
    0, 6, 0, 5, 0, 0, 0, 0, 9,
    0, 0, 4, 0, 0, 0, 0, 3, 0,
    0, 0, 0, 0, 0, 9, 7, 0, 0
};

// http://www.norvig.com/sudoku.html (puzzle 5 / 95)
const int SlowTestPuzzle[] = {
    0, 0, 0, 0, 1, 4, 0, 0, 0,
    0, 3, 0, 0, 0, 0, 2, 0, 0,
    0, 7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 9, 0, 0, 0, 3, 0,
    6, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 8, 0,
    2, 0, 0, 0, 0, 0, 1, 0, 4,
    0, 0, 0, 0, 5, 0, 6, 0, 0,
    0, 0, 0, 7, 0, 8, 0, 0, 0
};

void SolvePuzzle(const int* puzzle)
{
    SudokuGrid grid;

    int index = 0;

    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            auto value = puzzle[index++];

            if (value > 0)
                grid.Set(r, c, value - 1);
        }
    }

    grid.Solve();

    cout << grid;

    if (grid.IsSolved())
        cout << "SOLVED!\n";
    else if (!grid.CanBeSolved())
        cout << "cannot be solved\n";

    cout << endl;
}

void Solve95Puzzles()
{
    ifstream fin("top95.txt", ifstream::binary);

    if (fin)
    {
        ofstream fout("solve95.txt", ofstream::binary);

        char puzzle[96];

        for (int i = 0; fin && i < 95; ++i)
        {
            cout << "Solving problem " << (i + 1) << "..." << endl;
            fin.getline(puzzle, sizeof(puzzle));
            SudokuGrid grid;
            auto p = puzzle;

            for (int r = 0; r < 9; ++r)
            {
                for (int c = 0; c < 9; ++c)
                {
                    if (InRange(*p, '1', '9'))
                        grid.Set(r, c, *p - '1');

                    ++p;
                }
            }

            grid.Solve();
            fout << grid << '\n';
        }

        cout << "DONE!" << endl;

        fout.close();
        fin.close();
    }
}

void SolvePuzzles()
{
    SolvePuzzle(SlowTestPuzzle);
    SolvePuzzle(EasyTestPuzzle);
    SolvePuzzle(EvilTestPuzzle);
    SolvePuzzle(MotherTestPuzzle);

    const int EmptyPuzzle[81] = {};
    SolvePuzzle(EmptyPuzzle);
}

int main(int argc, char** argv)
{
    cout << "class size: " << sizeof(SudokuGrid) << " bytes\n";
    Solve95Puzzles();
    //SolvePuzzles();

    return 0;
}
