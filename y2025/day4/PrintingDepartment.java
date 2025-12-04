package y2025.day4;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Queue;
import java.util.Scanner;

public class PrintingDepartment {
    public static void main(String[] args) {
        Scanner sc = null;
        try {
            sc = new Scanner(new File("y2025/day4/input1.txt"));
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found: " + e.getMessage());
            System.exit(1);
        }
        ArrayList<String> input = new ArrayList<>();
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            input.add(line);
        }
        boolean isPartOne = false;
        System.out.println("Result: " + solve(input, isPartOne));
    }

    private static int solve(ArrayList<String> input, Boolean isPartOne) {
        int res = 0;
        int[][] directions = {
                { -1, -1 }, { -1, 0 }, { -1, 1 },
                { 0, 1 }, { 1, 1 }, { 1, 0 },
                { 1, -1 }, { 0, -1 }
        };
        int n = input.size(), m = input.get(0).length();
        if (isPartOne) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (input.get(i).charAt(j) != '@')
                        continue;
                    int count = 0;
                    for (int[] dir : directions) {
                        int y = i + dir[0], x = j + dir[1];
                        if (x >= 0 && y >= 0 && x < m && y < n) {
                            if (input.get(y).charAt(x) == '@')
                                count++;
                        }
                    }
                    if (count < 4)
                        res++;
                }
            }
        } else {
            char[][] grid = new char[n][m];
            for (int i = 0; i < n; i++)
                grid[i] = input.get(i).toCharArray();
            int[][] degree = new int[n][m];
            Queue<int[]> q = new ArrayDeque<>();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (grid[i][j] != '@')
                        continue;

                    int cnt = 0;
                    for (int[] d : directions) {
                        int y = i + d[0], x = j + d[1];
                        if (y >= 0 && x >= 0 && y < n && x < m && grid[y][x] == '@')
                            cnt++;
                    }
                    degree[i][j] = cnt;

                    if (cnt < 4)
                        q.add(new int[] { i, j }); // remove
                }
            }
            //BFS peeling
            while (!q.isEmpty()) {
                int[] cur = q.poll();
                int r = cur[0], c = cur[1];

                if (grid[r][c] != '@')
                    continue;
                grid[r][c] = '.';
                res++;

                for (int[] d : directions) {
                    int y = r + d[0], x = c + d[1];
                    if (y >= 0 && x >= 0 && y < n && x < m && grid[y][x] == '@') {
                        degree[y][x]--;
                        if (degree[y][x] == 3) {
                            q.add(new int[] { y, x });
                        }
                    }
                }
            }

        }

        return res;
    }
}
