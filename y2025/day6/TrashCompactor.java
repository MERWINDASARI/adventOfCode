package y2025.day6;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class TrashCompactor {

    private static ArrayList<List<Long>> problems = new ArrayList<>();
    private static ArrayList<Character> operations = new ArrayList<>();

    private static void parseInput(Scanner sc) {
        ArrayList<List<String>> rows = new ArrayList<>();

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            if (line.trim().isEmpty()) continue;

            String[] parts = line.trim().split("\\s+");
            ArrayList<String> row = new ArrayList<>();
            for (String p : parts) row.add(p);

            rows.add(row);
        }

        if (rows.isEmpty()) return;

        int problemCount = rows.get(0).size();

        for (int i = 0; i < problemCount; i++) {
            problems.add(new ArrayList<>());
        }

        int lastIndex = rows.size() - 1;

        for (int col = 0; col < problemCount; col++) {
            operations.add(rows.get(lastIndex).get(col).charAt(0));
        }

        for (int r = 0; r < lastIndex; r++) {
            for (int col = 0; col < problemCount; col++) {
                String s = rows.get(r).get(col);
                problems.get(col).add(Long.parseLong(s));
            }
        }
    }

    private static long solve() {
        long total = 0;

        for (int i = 0; i < problems.size(); i++) {
            List<Long> nums = problems.get(i);
            char op = operations.get(i);

            long result = (op == '*') ? 1 : 0;

            for (Long n : nums) {
                if (op == '*') result *= n;
                else result += n;
            }

            total += result;
        }

        return total;
    }

    public static void main(String[] args) {
        Scanner sc;

        try {
            sc = new Scanner(new File("y2025/day6/input1.txt"));
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found: " + e.getMessage());
            return;
        }

        parseInput(sc);

        long result = solve();
        System.out.println("Grand Total: " + result);
    }
}
