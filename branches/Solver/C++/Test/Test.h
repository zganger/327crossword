#pragma once
#pragma comment(lib, "SudokuLib.lib")

#include "..\SudokuLib\SudokuSolver.h"
#include <vector>

class Test
{
public:
	Test() { };
	~Test();

	// prints sudoku to stdout
	void PrintSudoku(int const * sudoku) const;

	// adds each 81-character line in fileName to _sudokus.
	// non-digit characters in a line are considered blank cells
	void AddSudokusFromFile(const char* fileName);

	// attempts to solve every sudoku in _sudokus
	// if verbose, unsolved puzzles are printed
	void SolveSudokus(bool verbose = false);

	// quickly verifies whether sudoku is solved
	bool Solved(int const * sudoku) const;

private:
	std::vector<int*> _sudokus;
};