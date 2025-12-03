package y2025.day2;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class GiftShop {
    private static boolean isValid(String s,Boolean isPartOne) {
        if(!isPartOne){
            String doubled = s + s;
            String chopped = doubled.substring(1, doubled.length() - 1);
            return !chopped.contains(s);
        }
        if (s.length() % 2 != 0) {
            return true;
        }
        int half = s.length() / 2;
        String firstHalf = s.substring(0, half);
        String secondHalf = s.substring(half);
        return !firstHalf.equals(secondHalf);
    }

    public static void main(String[] args) {
        Scanner sc = null;
        Boolean isPartOne=false;
        try {
            sc = new Scanner(new File("y2025/day2/input1.txt"));
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found: " + e.getMessage());
            System.exit(1);
        }

        String line = sc.nextLine();
        long res = 0;

        for (String range : line.split(",")) {
            String[] parts = range.split("-");
            long min = Long.parseLong(parts[0]);
            long max = Long.parseLong(parts[1]);

            for (long i = min; i <= max; i++) {
                if (!isValid(Long.toString(i),isPartOne)) {
                    res += i;
                }
            }
        }

        System.out.println("Result: " + res);
    }
}
