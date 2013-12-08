#include "SudokuSolver.h"
#include "Test.h"
#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

Test::~Test()
{
	for (size_t i = 0; i < _sudokus.size(); ++i)
		delete[] _sudokus[i];
}

// determines whether sudoku is solved
bool Test::Solved(int const * sudoku) const
{
	int row[9], column[9], box[9];
	int i, j, k;

	for (i = 0; i < 9; ++i)
	{
		k = 0;
		for (j = i * 9; j < (i * 9) + 9; ++j)
			row[k++] = sudoku[j];

		sort(begin(row), end(row));

		for (j = 0; j < 9; ++j)
			if (row[j] != j + 1)
				return false;

		k = 0;
		for (j = i; k < 9; j += 9)
			column[k++] = sudoku[j];

		sort(begin(column), end(column));

		for (j = 0; j < 9; ++j)
			if (column[j] != j + 1)
				return false;

		k = 0;
		for (j = (i * 3) % 9; k < 9; j += 9)
			for (int l = 0; l < 3; ++l)
				box[k++] = sudoku[j + l];

		sort(begin(box), end(box));

		for (j = 0; j < 9; ++j)
			if (box[j] != j + 1)
				return false;
	}

	return true;
}

void Test::AddSudokusFromFile(const char* fileName)
{
	ifstream file(fileName);
	if (!file)
		return;

	string line;
	while (getline(file, line))
	{
		if (line.length() < 81)
			continue;

		int* sudoku = new int[81];
		for (int i = 0; i < 81; ++i)
			sudoku[i] = isdigit(line[i]) ? line[i] - '0' : 0;

		_sudokus.push_back(sudoku);
	}

	file.close();
	return;
}

void Test::PrintSudoku(int const * sudoku) const
{
	for (int i = 0; i < 81;)
	{
		cout << sudoku[i] << " ";
		if (++i % 9 == 0)
			cout << endl;
	}

	cout << endl;
}

void Test::SolveSudokus(bool verbose)
{
	int valids = 0;
	vector<double>* const solveTimes = new vector<double>(_sudokus.size());
	
	SudokuSolver s;
	for (size_t i = 0; i < _sudokus.size(); ++i)
	{
		clock_t start = clock();
		s.Solve(_sudokus[i]);
		solveTimes->push_back( (clock() - start) / (CLOCKS_PER_SEC / 1000) );

		if (Solved(_sudokus[i]))
			++valids;
		else if (verbose)
		{
			cout << "Invalid solution: " << endl;
			PrintSudoku(_sudokus[i]);
		}
	}

	double totalTime = 0;
	double maxTime = 0;
	for (size_t i = 0; i < solveTimes->size(); ++i)
	{
		if ((*solveTimes)[i] > maxTime)
			maxTime = (*solveTimes)[i];
		totalTime += (*solveTimes)[i];
	}
	double avgTime = totalTime / solveTimes->size();

	cout << "Solved " << valids << " / " << _sudokus.size() << " sudokus averaging "
		 << setprecision(4) << avgTime << "ms per solution." << endl;
	cout << "Slowest: "  << maxTime << endl;

	delete solveTimes;
}