package Test;

import SudokuSolver.SudokuSolver;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

public class Test {
    private ArrayList<int[]> _sudokus = new ArrayList<int[]>();

    public Test() { }

    // prints sudoku to console
    public void PrintSudoku(int[] sudoku) {
        for (int i = 0; i < 81;) {
            System.out.printf("%d ", sudoku[i]);
            if (++i % 9 == 0)
                System.out.print("\n");
        }

        System.out.print("\n");
    }

    // adds each 81-character line in fileName to _sudokus.
    // non-digit characters in a line are considered blank cells
    public void AddSudokusFromFile(String fileName) throws IOException {
        BufferedReader file = new BufferedReader(new FileReader(fileName));
        while (file.ready()) {
            char[] chars = file.readLine().toCharArray();
            if (chars.length != 81)
                continue;
            int[] puzzle = new int[81];
            for (int i = 0; i < 81; ++i)
                puzzle[i] = Character.isDigit(chars[i]) ? Character.digit(chars[i], 10) : 0;
            _sudokus.add(puzzle);
        }
    }

    // attempts to solve every sudoku in _sudokus
    // if verbose, unsolved puzzles are printed
    public void SolveSudokus(boolean verbose) {
        int valids = 0;
        ArrayList<Long> solveTimes = new ArrayList<Long>(_sudokus.size());

        SudokuSolver s = new SudokuSolver(9);
        for (int[] sudoku : _sudokus)
        {
            long start = System.currentTimeMillis();
            s.Solve(sudoku);
            solveTimes.add(System.currentTimeMillis() - start);

            if (Solved(sudoku))
                ++valids;
            else if (verbose) {
                System.out.println("Invalid solution.");
                PrintSudoku(sudoku);
            }
        }

        double totalTime = 0;
        Long maxTime = Long.MIN_VALUE;
        for (Long time : solveTimes) {
            if (time > maxTime)
                maxTime = time;
            totalTime += time;
        }
        double avgTime = totalTime / solveTimes.size();

        System.out.printf("Solved %d / %d sudokus averaging %f ms per solution.", valids, _sudokus.size(), avgTime);
        System.out.printf("\nSlowest: %d ms.", maxTime);
    }

    // quickly verifies whether sudoku is solved
    public boolean Solved(int[] sudoku) {
        int[] row = new int[9];
        int[] column = new int[9];
        int[] box = new int[9];
        int i, j, k;

        for (i = 0; i < 9; ++i)
        {
            k = 0;
            for (j = i * 9; j < (i * 9) + 9; ++j)
                row[k++] = sudoku[j];

            Arrays.sort(row);

            for (j = 0; j < 9; ++j)
                if (row[j] != j + 1)
                    return false;

            k = 0;
            for (j = i; k < 9; j += 9)
                column[k++] = sudoku[j];

            Arrays.sort(column);

            for (j = 0; j < 9; ++j)
                if (column[j] != j + 1)
                    return false;

            k = 0;
            for (j = (i * 3) % 9; k < 9; j += 9)
                for (int l = 0; l < 3; ++l)
                    box[k++] = sudoku[j + l];

            Arrays.sort(box);

            for (j = 0; j < 9; ++j)
                if (box[j] != j + 1)
                    return false;
        }

        return true;
    }
}
