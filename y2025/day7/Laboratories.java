package y2025.day7;

import java.util.*;
import java.io.*;

public class Laboratories {

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

    private static String generateNextLevel(String previousLevel, String nextLevelTemplate) {
        StringBuilder nextLevel = new StringBuilder(nextLevelTemplate);
        int m = previousLevel.length();
        for (int i = 0; i < m; i++) {
            char ch = previousLevel.charAt(i);
            if (ch == '|') {
                if (nextLevelTemplate.charAt(i) == '^') {
                    if (i != 0 && nextLevel.charAt(i - 1) == '.')
                        nextLevel.setCharAt(i - 1, ch);
                    if (i != m - 1 && nextLevel.charAt(i + 1) == '.')
                        nextLevel.setCharAt(i + 1, ch);
                } else {
                    nextLevel.setCharAt(i, ch);
                }
            }
        }
        return nextLevel.toString();
    }

    private static List<String> simulate(List<String> lines) {
        int n = lines.size();
        List<String> snapshot = new ArrayList<>();
        snapshot.add(lines.get(0));
        snapshot.add(lines.get(0).replace('S', '|'));
        for (int i = 1; i < n - 1; i++) {
            snapshot.add(generateNextLevel(snapshot.get(i), lines.get(i + 1)));
        }
        return snapshot;
    }

    private static long[] calculateNextStrengths(long[] prevStrengths, String currentRowTemplate) {
        int m = prevStrengths.length;
        long[] nextStrengths = new long[m];

        for (int i = 0; i < m; i++) {
            long sum = 0;
            if (currentRowTemplate.charAt(i) != '^') {
                sum += prevStrengths[i];
            }
            if (i > 0 && currentRowTemplate.charAt(i - 1) == '^') {
                sum += prevStrengths[i - 1];
            }
            if (i < m - 1 && currentRowTemplate.charAt(i + 1) == '^') {
                sum += prevStrengths[i + 1];
            }
            nextStrengths[i] = sum;
        }
        return nextStrengths;
    }


    public static void main(String[] args) {
        List<String> lines = readFile("y2025/day7/input1.txt");
        Boolean isPartOne = false;
        int n = lines.size(), m = lines.get(0).length();
        List<String> beamLastSnapshot = simulate(lines);
        for (String level : beamLastSnapshot) {
            System.out.println(level);
        }

        long res = 0;
        if (isPartOne) {
            for (int i = 2; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (beamLastSnapshot.get(i).charAt(j) == '^' && beamLastSnapshot.get(i - 1).charAt(j) == '|') {
                        res++;
                    }
                }
            }
        } else {
            long[] currentStrengths = new long[m];
            String firstRow = lines.get(0);
            for (int i = 0; i < m; i++) {
                if (firstRow.charAt(i) == 'S') {
                    currentStrengths[i] = 1;
                } else {
                    currentStrengths[i] = 0;
                }
            }

            for (int i = 1; i < n; i++) {
                String currentRowTemplate = lines.get(i);
                currentStrengths = calculateNextStrengths(currentStrengths, currentRowTemplate);
            }

            for (long val : currentStrengths) {
                res += val;
            }
        }

        System.out.println("Result: " + res);
    }

}
