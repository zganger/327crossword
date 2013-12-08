#include "SudokuSolver.h"
#include "Test.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <vector>
using namespace std;

int main(int argc, char **argv) 
{
	{
		Test t;

		t.AddSudokusFromFile("Test Cases\\top1465.txt");         // 1465 ordinary sudokus
		t.AddSudokusFromFile("Test Cases\\HardestDatabase.txt"); // 375 particularly hard sudokus
		t.AddSudokusFromFile("Test Cases\\unsolvable.txt");      // 3 unsolvable sudokus
		t.SolveSudokus();
	}

	_CrtDumpMemoryLeaks(); // MSVC function to log memory leaks

	return 0;
}