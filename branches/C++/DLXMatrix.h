#pragma once
#include "DLXNode.h"
#include <vector>

// Owns the quadruply-linked circular lists DLX requires.
class DLXMatrix
{
public:
	DLXMatrix(int columns);
	DLXMatrix(const DLXMatrix&);
	~DLXMatrix(void);
	
	void AppendToColumn(DLXNode* DLXNode, int columnIndex);
	inline int AddRow(DLXNode* header) { _rows.push_back(header); return _rows.size() - 1;}
	inline DLXNode* Root() { return _root; }
	inline DLXNode* RowHeader(int rowIndex) { return _rows.at(rowIndex); }
	
private:
	std::vector<DLXNode*> _columns;
	DLXNode* _root;
	std::vector<DLXNode*> _rows;
	
	// creates the column list
	void CreateColumns();
};