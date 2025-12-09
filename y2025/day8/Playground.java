package y2025.day8;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

class UnionFind {
    int[] parent;
    int[] size;

    UnionFind(int n) {
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    boolean union(int a, int b) {
        int pa = find(a);
        int pb = find(b);

        if (pa == pb)
            return false; // already together

        // union by size
        if (size[pa] < size[pb]) {
            parent[pa] = pb;
            size[pb] += size[pa];
        } else {
            parent[pb] = pa;
            size[pa] += size[pb];
        }
        return true;
    }

    int clusterSize(int x) {
        return size[find(x)];
    }
}

public class Playground {
    private static List<List<Integer>> points = new ArrayList<>();

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
            int a = Integer.parseInt(parts[0].trim());
            int b = Integer.parseInt(parts[1].trim());
            int c = Integer.parseInt(parts[2].trim());

            points.add(Arrays.asList(a, b, c));
        }
    }

    public static void main(String[] args) {
        List<String> lines = readFile("y2025/day8/input1.txt");
        Boolean isPartOne = false;
        parseInput(lines);
        record Edge(int i, int j, double dist) {
        }
        List<Edge> edges = new ArrayList<>();

        for (int i = 0; i < points.size(); i++) {
            List<Integer> p1 = points.get(i);

            for (int j = i + 1; j < points.size(); j++) {
                List<Integer> p2 = points.get(j);

                double dx = p1.get(0) - p2.get(0);
                double dy = p1.get(1) - p2.get(1);
                double dz = p1.get(2) - p2.get(2);

                double dist = Math.sqrt(dx * dx + dy * dy + dz * dz);
                edges.add(new Edge(i, j, dist));
            }
        }
        edges.sort(Comparator.comparingDouble(Edge::dist));
        UnionFind uf = new UnionFind(points.size());
        if (isPartOne) {
            int k = 1000;
            for (Edge e : edges) {
                uf.union(e.i(), e.j());
                k--;
                if (k == 0)
                    break;
            }

            Map<Integer, Integer> clusterSizes = new HashMap<>();

            for (int i = 0; i < points.size(); i++) {
                int root = uf.find(i);
                clusterSizes.put(root, uf.size[root]);
            }

            List<Integer> big3clusters = clusterSizes.values()
                    .stream()
                    .sorted(Comparator.reverseOrder())
                    .limit(3)
                    .toList();
            System.out.println(big3clusters);
            System.out.println(
                    "Result: " + big3clusters.get(0) *
                            big3clusters.get(1) *
                            big3clusters.get(2));

        } else {
            Integer lastMergePoint1 = null;
            Integer lastMergePoint2 = null;

            for (Edge e : edges) {
                if (uf.union(e.i(), e.j())) {
                    lastMergePoint1 = e.i();
                    lastMergePoint2 = e.j();
                }
            }

            int x1 = points.get(lastMergePoint1).get(0);
            int x2 = points.get(lastMergePoint2).get(0);
            System.out.println(x1+"-"+x2);
            System.out.println("Resutl: "+x1*x2);
        }
    }

}
