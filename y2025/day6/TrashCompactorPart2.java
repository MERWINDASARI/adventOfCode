package y2025.day6;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class TrashCompactorPart2 {

    public static void main(String[] args) {
        List<String> lines = readFile("y2025/day6/input1.txt");
        long grandTotal = solve(lines);
        System.out.println("Grand Total: " + grandTotal);
    }

    // ---------------------------------------------------------------------

    private static List<String> readFile(String path) {
        List<String> lines = new ArrayList<>();
        try (Scanner sc = new Scanner(new File(path))) {
            while (sc.hasNextLine()) {
                lines.add(sc.nextLine());
            }
        } catch (FileNotFoundException e) {
            System.out.println("FILE NOT FOUND: " + e.getMessage());
            System.exit(1);
        }
        return lines;
    }

    // ---------------------------------------------------------------------

    /**
     * Solve the worksheet where problems are arranged in vertical blocks.
     */
    private static long solve(List<String> lines) {
        if (lines.isEmpty()) return 0;

        int rows = lines.size();
        int cols = lines.get(0).length();

        // Identify problem column blocks separated by at least 1 full space column
        List<int[]> blocks = new ArrayList<>();

        boolean inBlock = false;
        int start = 0;

        for (int c = 0; c < cols; c++) {
            boolean allSpace = true;
            for (int r = 0; r < rows; r++) {
                char ch = lines.get(r).charAt(c);
                if (ch != ' ' && ch != '.') {
                    allSpace = false;
                    break;
                }
            }

            if (!inBlock && !allSpace) {
                inBlock = true;
                start = c;
            }

            if (inBlock && allSpace) {
                inBlock = false;
                blocks.add(new int[]{start, c - 1});
            }
        }
        if (inBlock) {
            blocks.add(new int[]{start, cols - 1});
        }

        long grandTotal = 0;

        // Process each block RIGHT→LEFT
        for (int b = blocks.size() - 1; b >= 0; b--) {
            int[] block = blocks.get(b);
            long result = solveSingleProblem(lines, block[0], block[1]);
            //System.out.println("Res: " + result);
            grandTotal += result;
        }

        return grandTotal;
    }

    // ---------------------------------------------------------------------

    /**
     * Parse and compute one problem inside columns [cStart, cEnd]
     */
    private static long solveSingleProblem(List<String> lines, int cStart, int cEnd) {
        int rows = lines.size();

        // Operator is always on the last line of the block
        char op = findOperator(lines.get(rows - 1), cStart, cEnd);

        // Each vertical column inside block → one number
        List<Long> numbers = new ArrayList<>();

        for (int c = cStart; c <= cEnd; c++) {
            StringBuilder sb = new StringBuilder();
            for (int r = 0; r < rows - 1; r++) {
                char ch = lines.get(r).charAt(c);
                if (Character.isDigit(ch))
                    sb.append(ch);
            }
            if (sb.length() > 0) {
                numbers.add(Long.parseLong(sb.toString()));
            }
        }

        Collections.reverse(numbers);

        long result;
        if (op == '+') {
            result = 0;
            for (long n : numbers) result += n;
        } else { 
            result = 1;
            for (long n : numbers) result *= n;
        }

        return result;
    }

    // ---------------------------------------------------------------------

    private static char findOperator(String line, int cStart, int cEnd) {
        for (int c = cStart; c <= cEnd; c++) {
            char ch = line.charAt(c);
            if (ch == '+' || ch == '*') return ch;
        }
        throw new RuntimeException("No operator found in block: " + cStart + "-" + cEnd);
    }
}
