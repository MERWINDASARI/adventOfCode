package y2025.day11;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Reactor {

    private static Map<String, List<String>> graph = new HashMap<>();
    private static Map<String, Long> memo = new HashMap<>();
    private static Map<String, Long> memo2 = new HashMap<>();


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
            String[] parts = line.split(":");
            String from = parts[0].trim();

            graph.putIfAbsent(from, new ArrayList<>());

            if (parts.length > 1) {
                String[] tos = parts[1].trim().split("\\s+");
                for (String to : tos) {
                    graph.get(from).add(to);
                }
            }
        }
    }

    private static long countPaths(String node) {
        if (node.equals("out")) {
            return 1;
        }

        if (memo.containsKey(node)) {
            return memo.get(node);
        }

        long total = 0;
        for (String next : graph.getOrDefault(node, List.of())) {
            total += countPaths(next);
        }

        memo.put(node, total);
        return total;
    }

    private static long countPathsPart2(String node, boolean seenDac, boolean seenFft) {

        if (node.equals("dac"))
            seenDac = true;
        if (node.equals("fft"))
            seenFft = true;

        // Encode memo key
        String key = node + "|" + seenDac + "|" + seenFft;

        if (memo2.containsKey(key)) {
            return memo2.get(key);
        }

        if (node.equals("out")) {
            return (seenDac && seenFft) ? 1 : 0;
        }

        long total = 0;
        for (String next : graph.getOrDefault(node, List.of())) {
            total += countPathsPart2(next, seenDac, seenFft);
        }

        memo2.put(key, total);
        return total;
    }

    public static void main(String[] args) {
        List<String> lines = readFile("y2025/day11/input1.txt");
        parseInput(lines);

        boolean isPartOne = false;
        if (isPartOne) {
            long result = countPaths("you");
            System.out.println("Paths from you to out: " + result);
        } else {
            long result = countPathsPart2("svr", false, false);
            System.out.println("Paths from svr to out visiting dac and fft: " + result);
        }

    }
}
