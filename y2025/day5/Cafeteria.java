package y2025.day5;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

public class Cafeteria {
    private static ArrayList<List<Long>> ranges = new ArrayList<>();
    private static ArrayList<Long> ids = new ArrayList<>();

    private static void parseInput(Scanner sc) {
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            if (line.isEmpty())
                break;

            String[] parts = line.split("-");
            long min = Long.parseLong(parts[0]);
            long max = Long.parseLong(parts[1]);

            ranges.add(Arrays.asList(min, max));
        }

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            if (!line.isEmpty())
                ids.add(Long.parseLong(line));
        }
    }

    private static ArrayList<List<Long>> merge() {
        ArrayList<List<Long>> result = new ArrayList<>();

        long currentStart = ranges.get(0).get(0);
        long currentEnd = ranges.get(0).get(1);

        for (int i = 1; i < ranges.size(); i++) {
            long nextStart = ranges.get(i).get(0);
            long nextEnd = ranges.get(i).get(1);

            if (nextStart <= currentEnd) {
                currentEnd = Math.max(currentEnd, nextEnd);
            } else {
                result.add(Arrays.asList(currentStart, currentEnd));
                currentStart = nextStart;
                currentEnd = nextEnd;
            }
        }

        result.add(Arrays.asList(currentStart, currentEnd));
        return result;
    }

    public static void main(String[] args) {
        Scanner sc = null;
        Boolean isPartOne=false;
        try {
            sc = new Scanner(new File("y2025/day5/input1.txt"));
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found: " + e.getMessage());
            System.exit(1);
        }

        parseInput(sc);

        ranges.sort(
                Comparator.<List<Long>, Long>comparing(r -> r.get(0))
                        .thenComparing(r -> r.get(1)));

        ArrayList<List<Long>> mergedRanges = merge();
        long res = 0;
        if (isPartOne) {
            for (Long id : ids) {
                for (List<Long> range : mergedRanges) {
                    if (range.get(0) <= id && range.get(1) >= id) {
                        res++;
                        break;
                    }
                }
            }
        }else{
            for (List<Long> range : mergedRanges) {
                res+=range.get(1)-range.get(0)+1;
            }
        }

        System.out.println("Result: " + res);
    }
}
