#include "DLX.h"

DLX::DLX(void)
{
	_done = false;
}

DLX::~DLX(void)
{
	return;
}

DLXNode* DLX::ShortestColumn() const
{
	DLXNode* cursor = _matrix->Root()->right;
	DLXNode* shortestColumn = cursor;
	int minLength = cursor->data;

	while (cursor != _matrix->Root())
	{
		if (cursor->data < minLength)
		{
			shortestColumn = cursor;
			minLength = cursor->data;
		}
		cursor = (cursor->right);
	}
	
	return shortestColumn;
}

void DLX::Cover(DLXNode* columnHead)
{
	columnHead->right->left = columnHead->left;  // unlink the
	columnHead->left->right = columnHead->right; // column header
	
	for (DLXNode* row = columnHead->down; row != columnHead; row = row->down)
		for (DLXNode* col = row->right; col != row; col = col->right)
		{
			col->up->down = col->down; // for each row in the column
			col->down->up = col->up;   // unlink every node and
			col->column->data--;       // decrement the column length
		}
}

void DLX::Uncover(DLXNode* columnHead)
{
	// this is the inverse operation of Cover
	// note it's possible because the pointers of
	// covered (i.e. unlinked) nodes weren't modified
	for (DLXNode* row = columnHead->up; row != columnHead; row = row->up)
		for (DLXNode* col = row->left; col != row; col = col->left)
		{
			col->up->down = col;
			col->down->up = col;
			col->column->data++;
		}

	columnHead->right->left = columnHead; // relink the
	columnHead->left->right = columnHead; // header
}

void DLX::Solve(DLXMatrix* matrix, std::vector<int> const * givenRows)
{
	_matrix = matrix;

	if (givenRows)
		for (size_t i = 0; i < givenRows->size(); ++i)
			AddRowToSolution( (*givenRows)[i] );

	Recurse();
}

// each call covers one column
void DLX::Recurse()
{
	if (_matrix->Root()->right == _matrix->Root())
	{
		_done = true; // all columns covered,
		return;       // nothing left to do
	}

	DLXNode* column = ShortestColumn();
	Cover(column);

	DLXNode* row = column->down;
	while (row != column)
	{
		_solution.push(row);
		for (DLXNode* right = row->right; right != row; right = right->right)
			Cover(right->column);
		
		if (!_done)
			Recurse();
		if (_done)
			return;

		// if we're here, we need to backtrack
		_solution.pop();
		column = row->column;
		for (DLXNode* left = row->left; left != row; left = left->left)
			Uncover(left->column);

		row = row->down;
	}

	Uncover(column);
}

void DLX::AddRowToSolution(int rowIndex)
{
	DLXNode* node = _matrix->RowHeader(rowIndex);
	do
	{
		Cover(node->column);
		node = node->right;
	} while (node != _matrix->RowHeader(rowIndex));

	_solution.push(node);
}