#include "DLXMatrix.h"

// requiring a definite number of columns up front enables use
// of vector::at() below and only requires one allocation.
// DLXNodes could be added with vector::push_back followed at the end
// by vector::shrink_to_fit, but the latter is c++11
DLXMatrix::DLXMatrix(int columns)
{
	_root = new DLXNode;
	_root->right = _root->left = _root;
	_columns = std::vector<DLXNode*>(columns);
	CreateColumns();
	_rows = std::vector<DLXNode*>();
}

DLXMatrix::~DLXMatrix(void)
{
	for (size_t i = 0; i < _columns.size(); ++i)
		delete _columns[i];

	for (size_t i = 0; i < _rows.size(); ++i)
	{
		DLXNode* node = _rows[i]->right;
		while (node != _rows[i])
		{
			DLXNode* temp = node->right;
			delete node;
			node = temp;
		}
		delete _rows[i];
	}

	delete _root;
}

void DLXMatrix::CreateColumns()
{
	for (size_t i = 0; i < _columns.size(); ++i)
	{
		DLXNode* node = new DLXNode;
		node->index = i;
		node->left = _root->left;
		node->right = _root;
		node->up = node->down = node->column = node;

		_root->left->right = node;
		_root->left = node;

		_columns[i] = node;
	}
}

// append DLXNode at the end of columnHeader's list
void DLXMatrix::AppendToColumn(DLXNode* node, int columnIndex)
{
	// note the column is circular: header->up points to
	// the end of the list and end->down points to header

	// TODO: at() throws
	DLXNode* columnHeader = _columns.at(columnIndex);
	node->column = node->down = columnHeader;
	node->up = columnHeader->up;
	columnHeader->up->down = node;
	columnHeader->up = node;

	columnHeader->data++;
}