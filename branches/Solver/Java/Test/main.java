package Test;

import java.io.IOException;

public class main {

    public static void main(String[] args) {
        Test t = new Test();
        System.out.println("Working Directory = " +
                System.getProperty("user.dir"));
        try {
            t.AddSudokusFromFile("HardestDatabase.txt"); // 375 particularly hard sudokus
            t.AddSudokusFromFile("top1465.txt");         // 1465 ordinary sudokus
            t.AddSudokusFromFile("unsolvable.txt");      // 3 unsolvable sudokus
        } catch (IOException e) {
            return;
        }

        t.SolveSudokus(true);

        return;
    }
}