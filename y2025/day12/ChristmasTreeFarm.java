
package y2025.day12;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class ChristmasTreeFarm {
    static class Shape {
        int id;
        List<String> grid;
    }

    static class Orientation {
        int[][] cells;
        int width, height;
    }

    static class Region {
        int width;
        int height;
        int[] counts;
    }

    private static List<Shape> shapes = new ArrayList<>();
    private static List<Region> regions = new ArrayList<>();

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

        int i = 0;

        // ---------- Parse shapes ----------
        while (i < lines.size()) {
            String line = lines.get(i).trim();

            if (line.isEmpty()) {
                i++;
                continue;
            }

            // Region section starts when we see WxH:
            if (line.contains("x") && line.contains(":")) {
                break;
            }

            // Shape header: "0:"
            if (line.endsWith(":")) {
                Shape shape = new Shape();
                shape.id = Integer.parseInt(line.substring(0, line.length() - 1));
                shape.grid = new ArrayList<>();

                i++;
                while (i < lines.size()) {
                    String row = lines.get(i).trim();
                    if (row.isEmpty() || row.contains(":")) {
                        break;
                    }
                    shape.grid.add(row);
                    i++;
                }
                shapes.add(shape);
            } else {
                i++;
            }
        }

        // ---------- Parse regions ----------
        while (i < lines.size()) {
            String line = lines.get(i).trim();
            i++;

            if (line.isEmpty())
                continue;

            // Example: "12x5: 1 0 1 0 2 2"
            String[] parts = line.split(":");
            String[] dims = parts[0].split("x");

            Region region = new Region();
            region.width = Integer.parseInt(dims[0]);
            region.height = Integer.parseInt(dims[1]);

            String[] nums = parts[1].trim().split("\\s+");
            region.counts = new int[nums.length];
            for (int j = 0; j < nums.length; j++) {
                region.counts[j] = Integer.parseInt(nums[j]);
            }

            regions.add(region);
        }

        // System.out.println("Shapes:");
        // for (Shape s : shapes) {
        // System.out.println("Shape " + s.id);
        // for (String row : s.grid) {
        // System.out.println(row);
        // }
        // System.out.println();
        // }

        // System.out.println("Regions:");
        // for (Region r : regions) {
        // System.out.print(r.width + "x" + r.height + ": ");
        // for (int c : r.counts) {
        // System.out.print(c + " ");
        // }
        // System.out.println();
        // }
    }

    private static List<Orientation> generateOrientations(Shape shape) {
        List<int[]> base = new ArrayList<>();
        for (int y = 0; y < shape.grid.size(); y++) {
            for (int x = 0; x < shape.grid.get(y).length(); x++) {
                if (shape.grid.get(y).charAt(x) == '#') {
                    base.add(new int[] { x, y });
                }
            }
        }

        List<Orientation> result = new ArrayList<>();

        for (int flip = 0; flip < 2; flip++) {
            for (int rot = 0; rot < 4; rot++) {
                List<int[]> t = new ArrayList<>();

                for (int[] c : base) {
                    int x = c[0], y = c[1];
                    if (flip == 1)
                        x = -x;
                    for (int r = 0; r < rot; r++) {
                        int tmp = x;
                        x = y;
                        y = -tmp;
                    }
                    t.add(new int[] { x, y });
                }

                // normalize
                int minX = Integer.MAX_VALUE, minY = Integer.MAX_VALUE;
                for (int[] c : t) {
                    minX = Math.min(minX, c[0]);
                    minY = Math.min(minY, c[1]);
                }
                for (int[] c : t) {
                    c[0] -= minX;
                    c[1] -= minY;
                }

                // dedupe
                boolean duplicate = false;
                for (Orientation o : result) {
                    if (sameCells(o.cells, t)) {
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate)
                    continue;

                int maxX = 0, maxY = 0;
                for (int[] c : t) {
                    maxX = Math.max(maxX, c[0]);
                    maxY = Math.max(maxY, c[1]);
                }

                Orientation o = new Orientation();
                o.cells = t.toArray(new int[0][]);
                o.width = maxX + 1;
                o.height = maxY + 1;
                result.add(o);
            }
        }
        return result;
    }

    private static boolean sameCells(int[][] a, List<int[]> b) {
        if (a.length != b.size())
            return false;
        for (int[] c : a) {
            boolean found = false;
            for (int[] d : b) {
                if (c[0] == d[0] && c[1] == d[1]) {
                    found = true;
                    break;
                }
            }
            if (!found)
                return false;
        }
        return true;
    }

    private static int part1Solve() {
        int count = 0;

        System.out.println("[INFO] Precomputing orientations for each shape");
        List<List<Orientation>> allOrients = new ArrayList<>();
        for (Shape s : shapes) {
            allOrients.add(generateOrientations(s));
        }
        System.out.println("[INFO] Done Precomputing orientations");
        System.out.println("[INFO] Solving each region");
        for (Region r : regions) {

            System.out.print(r.width + "x" + r.height + ": ");
            for (int c : r.counts) {
                System.out.print(c + " ");
            }
            System.out.println();

            boolean[][] grid = new boolean[r.height][r.width];

            List<List<Orientation>> presents = new ArrayList<>();
            int totalCells = 0;

            for (int i = 0; i < r.counts.length; i++) {
                for (int k = 0; k < r.counts[i]; k++) {
                    presents.add(allOrients.get(i));
                    totalCells += allOrients.get(i).get(0).cells.length;
                }
            }

            // Area prune
            if (totalCells > r.width * r.height)
                continue;

            if (solveRegion(grid, presents, 0)) {
                count++;
            }
        }

        return count;
    }

    private static boolean solveRegion(boolean[][] grid, List<List<Orientation>> presents, int idx) {
        if (idx == presents.size())
            return true;

        int H = grid.length, W = grid[0].length;

        for (Orientation o : presents.get(idx)) {
            for (int y = 0; y <= H - o.height; y++) {
                for (int x = 0; x <= W - o.width; x++) {
                    if (canPlace(grid, o, x, y)) {
                        place(grid, o, x, y, true);
                        if (solveRegion(grid, presents, idx + 1))
                            return true;
                        place(grid, o, x, y, false);
                    }
                }
            }
        }
        return false;
    }

    private static boolean canPlace(boolean[][] grid, Orientation o, int x, int y) {
        for (int[] c : o.cells) {
            if (grid[y + c[1]][x + c[0]])
                return false;
        }
        return true;
    }

    private static void place(boolean[][] grid, Orientation o, int x, int y, boolean v) {
        for (int[] c : o.cells) {
            grid[y + c[1]][x + c[0]] = v;
        }
    }

    public static void main(String[] args) {
        List<String> lines = readFile("y2025/day12/input.txt");
        parseInput(lines);
        System.out.println("Result: " + part1Solve());
    }

}
