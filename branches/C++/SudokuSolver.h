#pragma once
#include <stack>
#include <vector>
#include "DLX.h"
#include "DLXMatrix.h"
#include "DLXNode.h"

// Encapsulates the reduction of a sudoku to an EXACT COVER instance and
// its solution via DLX.  Users need only call Solve.
class SudokuSolver
{
public:
	SudokuSolver(int dimension = 9);
	SudokuSolver(const SudokuSolver&);
	~SudokuSolver(void);

	// Solves sudoku in place, returns a bool to indicate success/failure.
	bool Solve(int sudoku[]);

private:
	int _boxDimension;
	int _cells;
	std::vector<DLXNode*> _columns;
	int _dimension;
	DLX* _dlx;
	std::vector<int> _givenRows;
	DLXMatrix* _matrix;
	std::stack<DLXNode*>* _solution;
	int* _sudoku;

	// computes the index of the column encoding the constraint on a and b
	inline int ConstraintColumnIndex(int a, int b, int offset = 0) const
	{
		return (a * _dimension) + b + (offset * _cells);
	}

	// computes the grid (row, column) coordinate of a constraint column
	inline void ConstraintRowColumn(int columnIndex, int& a, int& b) const
	{
		a = columnIndex / _dimension;
		b = columnIndex % _dimension;
	}

	/* 
	returns the index of the box containing (row, column)
	in a 9x9 sudoku, boxes are indexed
				0 1 2
				3 4 5
				6 7 8
	and each contains 3 * 3 = 9 cells
	*/
	inline int BoxIndex(int row, int column) const
	{ 
		return (row - (row % _boxDimension)) + (column / _boxDimension);
	}

	// converts a (row, column) coordinate to an index into the one-dimensional sudoku array
	inline int FlatArrayIndex(int row, int column) const { return row * _dimension + column; }

	bool OutputSolution();
	int CreateRow(int row, int column, int value);
	void BuildMatrix();
	void Reset();
};