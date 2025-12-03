package y2025.day3;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Scanner;

public class Loby {
    public static void main(String[] args) {
        Scanner sc = null;
        Boolean isPartOne = false;
        try {
            sc = new Scanner(new File("y2025/day3/input1.txt"));
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found: " + e.getMessage());
            System.exit(1);
        }
        long res = 0;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            res += getMaxJoltage(line,isPartOne);
        }
        System.out.println("Result: " + res);
    }

    private static long getMaxJoltage(String line, Boolean isPartOne) {
        long k = 12;
        if(isPartOne) k=2;
        long toRemove = line.length() - k;

        Deque<Character> stack = new ArrayDeque<>();

        for (char c : line.toCharArray()) {
            while (!stack.isEmpty() && toRemove > 0 && stack.peekLast() < c) {
                stack.removeLast();
                toRemove--;
            }
            stack.addLast(c);
        }
        while (stack.size() > k) {
            stack.removeLast();
        }
        StringBuilder sb = new StringBuilder();
        for (char c : stack)
            sb.append(c);

        return Long.parseLong(sb.toString());
    }

}
