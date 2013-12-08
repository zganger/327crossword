#pragma once
#include <stack>
#include <vector>
#include "DLXMatrix.h"
#include "DLXNode.h"

// DLX solves an instance of EXACT COVER via a recursive, depth-first brute-force search.
// This search is surprisingly fast (though still not polynomial) because of the unique
// matrix structure it uses to encode the EXACT COVER matrix.
class DLX
{
public:
	DLX(void);
	~DLX(void);

	inline std::stack<DLXNode*>* Solution() { return &_solution; }

	// adds the given rows to the solution then begins the recursive search
	void Solve(DLXMatrix* matrix, std::vector<int> const * givenRows = nullptr);

private:
	bool _done;
	DLXMatrix* _matrix;
	std::stack<DLXNode*> _solution;
	
	// used to mark matrix rows as given before solving begins
	void AddRowToSolution(int rowIndex);

	// Cover marks a column (i.e. a constraint) satisfied by removing it
	// from the list of columns.  Its links, however, are preserved,
	// making it easy (and fast) to unmark (Uncover) the column when a
	// search branch results in failure and backtracking is required.
	void Cover(DLXNode* columnHead);

	// the recursive search function; covers one column per call
	// in English:
	// (1) chooses an unsatisfied constraint (a column of the matrix)
	// (2) chooses a row that satisfies this constraint (a node in the selected column's up-down list)
	// (3) adds that row to the solution (push a node from the row onto the solution stack)
	// (4) covers the column and removes from consideration all rows linked to those columns
	//     (because the constraints those columns represent are now satisfied)
	// .. and eventually all columns are covered and the cardinality of the solution stack
	// indicates whether an exact cover has been found.
	// In the case of standard sudoku, if the solution stack's cardinality is 81, it encodes
	// a consistent assignment of values to each of the puzzle's cells; if not, no such
	// assignment exists.
	void Recurse();

	// covering the shortest column is a fail-early strategy that
	// significantly speeds up the search
	DLXNode* ShortestColumn() const;

	// the inverse operation of Cover, Uncover relinks an unlinked column header
	void Uncover(DLXNode* columnHead);
};