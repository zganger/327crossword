#pragma once

// Node structure for use in the matrix manipulated by DLX.
// All fields are public because the algorithm will make
// thousands of modifications to them--the overhead of calling
// getter/setter functions every time is substantial.
class DLXNode
{
public:
	DLXNode(void);
	~DLXNode(void);

	DLXNode* column;
	DLXNode* left;
	DLXNode* right;
	DLXNode* up;
	DLXNode* down;

	int index; // row and column headers hold their own indices
	int data; // holds the length of a column for column headers
};