package y2025.day9;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class MovieTheater {
    private static List<long[]> points = new ArrayList<>();

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

    private static void parseInput(List<String> lines) {
        for (String line : lines) {
            String[] parts = line.split(",");
            long x = Long.parseLong(parts[0].trim());
            long y = Long.parseLong(parts[1].trim());
            points.add(new long[]{x, y});
        }
    }

    // Merge a new interval [start,end] into a list of sorted, non-overlapping intervals
    private static void addInterval(List<long[]> intervals, long start, long end) {
        List<long[]> newIntervals = new ArrayList<>();
        boolean added = false;
        for (long[] cur : intervals) {
            if (end + 1 < cur[0]) {
                if (!added) {
                    newIntervals.add(new long[]{start, end});
                    added = true;
                }
                newIntervals.add(cur);
            } else if (start > cur[1] + 1) {
                newIntervals.add(cur);
            } else {
                start = Math.min(start, cur[0]);
                end = Math.max(end, cur[1]);
            }
        }
        if (!added) {
            newIntervals.add(new long[]{start, end});
        }
        intervals.clear();
        intervals.addAll(newIntervals);
    }

    public static void main(String[] args) {
        List<String> lines = readFile("y2025/day9/input1.txt");
        parseInput(lines);

        int n = points.size();
        long res = 0;

        Set<Long> red = new HashSet<>();
        Map<Long, List<long[]>> greenIntervals = new HashMap<>();

        // Add red tiles
        for (long[] p : points) {
            long x = p[0], y = p[1];
            red.add((y << 32) | x);
            greenIntervals.putIfAbsent(y, new ArrayList<>());
            addInterval(greenIntervals.get(y), x, x); // red tile is also green
        }

        // Fill straight lines between consecutive red tiles
        for (int i = 0; i < n; i++) {
            long[] p1 = points.get(i);
            long[] p2 = points.get((i + 1) % n);
            long x1 = p1[0], y1 = p1[1];
            long x2 = p2[0], y2 = p2[1];

            if (y1 == y2) { // horizontal
                greenIntervals.putIfAbsent(y1, new ArrayList<>());
                addInterval(greenIntervals.get(y1), Math.min(x1, x2), Math.max(x1, x2));
            } else if (x1 == x2) { // vertical
                long minY = Math.min(y1, y2);
                long maxY = Math.max(y1, y2);
                for (long y = minY; y <= maxY; y++) {
                    greenIntervals.putIfAbsent(y, new ArrayList<>());
                    addInterval(greenIntervals.get(y), x1, x1);
                }
            }
        }

        // Fill interior of loop row by row
        long minY = Long.MAX_VALUE, maxY = Long.MIN_VALUE;
        long minX = Long.MAX_VALUE, maxX = Long.MIN_VALUE;
        for (long[] p : points) {
            minX = Math.min(minX, p[0]);
            maxX = Math.max(maxX, p[0]);
            minY = Math.min(minY, p[1]);
            maxY = Math.max(maxY, p[1]);
        }

        for (long y = minY; y <= maxY; y++) {
            List<long[]> row = greenIntervals.get(y);
            if (row == null || row.isEmpty()) continue;
            long left = row.get(0)[0];
            long right = row.get(0)[1];
            for (long[] interval : row) {
                left = Math.min(left, interval[0]);
                right = Math.max(right, interval[1]);
            }
            addInterval(row, left, right); // fill interior for this row
        }

        // Check all pairs of red tiles as opposite corners
        for (long[] p1 : points) {
            for (long[] p2 : points) {
                long x1 = p1[0], y1 = p1[1];
                long x2 = p2[0], y2 = p2[1];

                if (x1 == x2 && y1 == y2) continue;

                long minXRect = Math.min(x1, x2);
                long maxXRect = Math.max(x1, x2);
                long minYRect = Math.min(y1, y2);
                long maxYRect = Math.max(y1, y2);

                boolean valid = true;
                for (long y = minYRect; y <= maxYRect; y++) {
                    List<long[]> intervals = greenIntervals.get(y);
                    if (intervals == null) {
                        valid = false;
                        break;
                    }
                    boolean covered = false;
                    for (long[] interval : intervals) {
                        if (interval[0] <= minXRect && interval[1] >= maxXRect) {
                            covered = true;
                            break;
                        }
                    }
                    if (!covered) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    long area = (maxXRect - minXRect + 1) * (maxYRect - minYRect + 1);
                    res = Math.max(res, area);
                }
            }
        }

        System.out.println("Result: " + res);
    }
}
