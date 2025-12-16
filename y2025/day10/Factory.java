package y2025.day10;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Factory {

    static class MachineConfig {
        int nLights;
        int targetMask; // for part 1
        int[] buttons; // bitmasks describing button effects
        List<Integer> joltage; // for part 2
    }

    private static List<MachineConfig> machineConfigs;

    // ------------------------------------------------------------
    // INPUT PARSER
    // ------------------------------------------------------------
    private static List<String> readFile(String path) {
        List<String> lines = new ArrayList<>();
        try (Scanner sc = new Scanner(new File(path))) {
            while (sc.hasNextLine()) {
                String s = sc.nextLine().trim();
                if (!s.isEmpty())
                    lines.add(s);
            }
        } catch (FileNotFoundException e) {
            System.out.println("FILE NOT FOUND: " + e.getMessage());
            System.exit(1);
        }
        return lines;
    }

    private static void parseInput(List<String> lines) {
        machineConfigs = new ArrayList<>();

        for (String line : lines) {
            MachineConfig cfg = new MachineConfig();

            // Parse indicator light pattern [...]
            int l = line.indexOf('[');
            int r = line.indexOf(']');
            String pattern = line.substring(l + 1, r).trim();

            cfg.nLights = pattern.length();
            cfg.targetMask = 0;

            for (int i = 0; i < cfg.nLights; i++) {
                if (pattern.charAt(i) == '#')
                    cfg.targetMask |= (1 << i);
            }

            // Parse button patterns (...)
            List<int[]> rawButtons = new ArrayList<>();
            int idx = 0;
            while (true) {
                int i1 = line.indexOf('(', idx);
                if (i1 == -1)
                    break;
                int i2 = line.indexOf(')', i1);

                String inside = line.substring(i1 + 1, i2).trim();
                if (!inside.isEmpty()) {
                    String[] parts = inside.split(",");
                    int[] arr = new int[parts.length];
                    for (int k = 0; k < parts.length; k++)
                        arr[k] = Integer.parseInt(parts[k].trim());
                    rawButtons.add(arr);
                }
                idx = i2 + 1;
            }

            cfg.buttons = new int[rawButtons.size()];
            for (int bi = 0; bi < rawButtons.size(); bi++) {
                int mask = 0;
                for (int x : rawButtons.get(bi))
                    mask |= (1 << x);
                cfg.buttons[bi] = mask;
            }

            // Parse joltage {...}
            cfg.joltage = new ArrayList<>();
            int jl = line.indexOf('{');
            int jr = line.indexOf('}');
            if (jl != -1 && jr != -1) {
                String inside = line.substring(jl + 1, jr).trim();
                if (!inside.isEmpty()) {
                    String[] nums = inside.split(",");
                    for (String s : nums)
                        cfg.joltage.add(Integer.parseInt(s.trim()));
                }
            }

            machineConfigs.add(cfg);
        }
    }

    // ------------------------------------------------------------
    // PART 1 SOLVER (GF(2), minimize popcount)
    // ------------------------------------------------------------
    private static int solveMachinePart1(MachineConfig cfg) {
        int nLights = cfg.nLights;
        int nButtons = cfg.buttons.length;

        // Build row-based augmented matrix:
        // each row: mask of buttons that affect that light, plus RHS bit in separate
        // array
        int[] mat = new int[nLights]; // bitmask of buttons for each row
        int[] rhs = new int[nLights]; // 0/1 target for each row

        for (int i = 0; i < nLights; i++) {
            int mask = 0;
            for (int b = 0; b < nButtons; b++) {
                if (((cfg.buttons[b] >> i) & 1) == 1)
                    mask |= (1 << b);
            }
            mat[i] = mask;
            rhs[i] = (cfg.targetMask >> i) & 1;
        }

        // Gaussian elimination (row-echelon) on mat rows by columns (buttons)
        int row = 0;
        int[] pivotColForRow = new int[nLights]; // pivot column index for each row (or -1)
        Arrays.fill(pivotColForRow, -1);

        for (int col = 0; col < nButtons && row < nLights; col++) {
            // find row r >= row with bit 'col' set
            int sel = -1;
            for (int r = row; r < nLights; r++) {
                if (((mat[r] >> col) & 1) == 1) {
                    sel = r;
                    break;
                }
            }
            if (sel == -1)
                continue;

            // swap sel <-> row
            if (sel != row) {
                int tmp = mat[sel];
                mat[sel] = mat[row];
                mat[row] = tmp;
                int t2 = rhs[sel];
                rhs[sel] = rhs[row];
                rhs[row] = t2;
            }

            pivotColForRow[row] = col;

            // eliminate this column from all other rows
            for (int r = 0; r < nLights; r++) {
                if (r != row && (((mat[r] >> col) & 1) == 1)) {
                    mat[r] ^= mat[row];
                    rhs[r] ^= rhs[row];
                }
            }

            row++;
        }

        int rank = row;

        // Check for inconsistency: a row with zero mask but rhs = 1
        for (int r = rank; r < nLights; r++) {
            if (mat[r] == 0 && rhs[r] == 1) {
                // No solution; problem statement implies this shouldn't happen, but just in
                // case:
                return Integer.MAX_VALUE / 2;
            }
        }

        // Determine pivot column -> row mapping for back-substitution
        // Create array pivotRowForCol[col] = row index or -1 if free
        int[] pivotRowForCol = new int[nButtons];
        Arrays.fill(pivotRowForCol, -1);
        for (int r = 0; r < rank; r++) {
            int c = pivotColForRow[r];
            if (c >= 0)
                pivotRowForCol[c] = r;
        }

        // Collect free columns
        List<Integer> freeCols = new ArrayList<>();
        for (int c = 0; c < nButtons; c++)
            if (pivotRowForCol[c] == -1)
                freeCols.add(c);
        int F = freeCols.size();

        // Prepare to compute minimal weight among all free assignments
        int best = Integer.MAX_VALUE;

        // We will enumerate 2^F assignments. If F is large, you may wish to bail or
        // apply heuristics,
        // but typical inputs (AoC style) keep F small.
        int combos = 1 << F;
        for (int mask = 0; mask < combos; mask++) {
            // x[col] will hold final button choices for this assignment
            int[] x = new int[nButtons];

            // set free variables according to mask
            for (int i = 0; i < F; i++) {
                int col = freeCols.get(i);
                x[col] = (mask >> i) & 1;
            }

            // Back-substitute pivot variables from bottom (row = rank-1..0)
            for (int r = rank - 1; r >= 0; r--) {
                int pc = pivotColForRow[r];
                // compute sum of (mat[r] & x) over non-pc bits
                int rowMask = mat[r];
                // ensure pivot bit is set in rowMask (it should be)
                // we calculate rhs[r] XOR sum_{j != pc} (rowMask_j * x[j])
                int sum = 0;
                int m = rowMask & (~(1 << pc)); // all columns except pivot
                while (m != 0) {
                    int low = m & -m;
                    int j = Integer.numberOfTrailingZeros(low);
                    sum ^= x[j];
                    m ^= low;
                }
                x[pc] = rhs[r] ^ sum;
            }

            // compute Hamming weight of x
            int weight = 0;
            for (int c = 0; c < nButtons; c++)
                weight += x[c];
            if (weight < best)
                best = weight;
        }

        return best;
    }

    // ------------------------------------------------------------
    // PART 2 SOLVER (Integer Linear Programming via RREF + Search)
    // ------------------------------------------------------------
    private static long solveMachinePart2(MachineConfig cfg) {
        int numRows = cfg.joltage.size(); // Constraints (Counters)
        int numCols = cfg.buttons.length; // Variables (Buttons)

        // Convert inputs to double for RREF
        // Matrix: [Rows][Cols + 1] (Augmented)
        double[][] mat = new double[numRows][numCols + 1];
        long[] targets = cfg.joltage.stream().mapToLong(i -> i).toArray();

        // Fill Matrix
        // A[i][j] = 1 if button j affects counter i, else 0
        for (int r = 0; r < numRows; r++) {
            for (int c = 0; c < numCols; c++) {
                if (((cfg.buttons[c] >> r) & 1) == 1) {
                    mat[r][c] = 1.0;
                }
            }
            mat[r][numCols] = targets[r];
        }

        // 1. Gaussian Elimination to Reduced Row Echelon Form (RREF)
        int pivotRow = 0;
        int[] pivotColForRow = new int[numRows];
        Arrays.fill(pivotColForRow, -1);
        boolean[] isPivotCol = new boolean[numCols];

        for (int col = 0; col < numCols && pivotRow < numRows; col++) {
            // Find pivot
            int sel = pivotRow;
            while (sel < numRows && Math.abs(mat[sel][col]) < 1e-9) {
                sel++;
            }
            if (sel == numRows) continue; // Column is free

            // Swap rows
            double[] tmp = mat[pivotRow];
            mat[pivotRow] = mat[sel];
            mat[sel] = tmp;

            // Normalize row
            double div = mat[pivotRow][col];
            for (int j = col; j <= numCols; j++) {
                mat[pivotRow][j] /= div;
            }

            // Eliminate other rows
            for (int i = 0; i < numRows; i++) {
                if (i != pivotRow && Math.abs(mat[i][col]) > 1e-9) {
                    double factor = mat[i][col];
                    for (int j = col; j <= numCols; j++) {
                        mat[i][j] -= factor * mat[pivotRow][j];
                    }
                }
            }

            pivotColForRow[pivotRow] = col;
            isPivotCol[col] = true;
            pivotRow++;
        }

        // Check consistency: if any row is 0=1 (or 0=non-zero)
        for (int r = pivotRow; r < numRows; r++) {
            if (Math.abs(mat[r][numCols]) > 1e-5) {
                return 0; // Inconsistent system, no solution. Return 0 presses (or handle as error)
            }
        }

        // 2. Separate Free and Pivot Variables
        // Equation for pivot i: x_pivot + sum(coeff * x_free) = rhs
        // => x_pivot = rhs - sum(coeff * x_free)
        
        List<Integer> freeCols = new ArrayList<>();
        // Determine approximate bounds for free variables based on raw constraints
        // Since A*x = b and A>=0, x_j <= b_i (if A_ij > 0). 
        // We calculate a global tight bound for each free variable to limit search.
        int[] freeVarUpperBounds = new int[numCols];
        Arrays.fill(freeVarUpperBounds, Integer.MAX_VALUE);

        for (int c = 0; c < numCols; c++) {
            if (!isPivotCol[c]) {
                freeCols.add(c);
                // Simple bound: check which counters this button affects
                int mask = cfg.buttons[c];
                long minBound = Long.MAX_VALUE;
                for(int r=0; r<numRows; r++) {
                    if(((mask >> r) & 1) == 1) {
                         minBound = Math.min(minBound, targets[r]);
                    }
                }
                if(minBound != Long.MAX_VALUE) {
                    freeVarUpperBounds[c] = (int)minBound;
                } else {
                    // Button affects nothing? (Unlikely in puzzle)
                    // If it affects nothing, we should never press it (cost minimization).
                    freeVarUpperBounds[c] = 0; 
                }
            }
        }

        minTotalPresses = Long.MAX_VALUE;
        int[] currentFreeValues = new int[freeCols.size()];
        
        // 3. Recursive Search over Free Variables
        searchFreeVars(0, currentFreeValues, freeCols, mat, pivotColForRow, pivotRow, freeVarUpperBounds);

        return minTotalPresses == Long.MAX_VALUE ? 0 : minTotalPresses;
    }

    private static long minTotalPresses;

    private static void searchFreeVars(int idx, int[] freeValues, List<Integer> freeCols, 
                                       double[][] rref, int[] pivotColForRow, int rank, int[] bounds) {
        
        if (idx == freeCols.size()) {
            // Base case: All free vars assigned. Calculate Pivot vars.
            long currentTotal = 0;
            
            // Sum free vars
            for (int v : freeValues) currentTotal += v;
            
            // Calculate pivot variables
            // x_p = rhs - sum(mat[r][free_c] * free_val)
            for (int r = 0; r < rank; r++) {
                double val = rref[r][rref[0].length - 1]; // RHS
                for (int i = 0; i < freeCols.size(); i++) {
                    int fc = freeCols.get(i);
                    val -= rref[r][fc] * freeValues[i];
                }
                
                // Check if integer and non-negative
                if (val < -1e-5) return; // Negative presses invalid
                long longVal = Math.round(val);
                if (Math.abs(val - longVal) > 1e-5) return; // Not an integer
                
                currentTotal += longVal;
            }
            
            if (currentTotal < minTotalPresses) {
                minTotalPresses = currentTotal;
            }
            return;
        }

        // Recursive step: Iterate this free variable
        int colIndex = freeCols.get(idx);
        int maxVal = bounds[colIndex];
        
        // Optimization: Don't search if we already exceed found min
        // (Rough pruning, strict sum checked at base)
        
        for (int v = 0; v <= maxVal; v++) {
            freeValues[idx] = v;
            searchFreeVars(idx + 1, freeValues, freeCols, rref, pivotColForRow, rank, bounds);
        }
    }

    // ------------------------------------------------------------
    // MAIN
    // ------------------------------------------------------------
    public static void main(String[] args) {
        List<String> lines = readFile("y2025/day10/input1.txt");
        parseInput(lines);

        int total = 0;
        boolean isPartOne = false;
        for (MachineConfig cfg : machineConfigs) {
            if (isPartOne) {
                total += solveMachinePart1(cfg);
            } else {
                total += solveMachinePart2(cfg);

            }
        }

        System.out.println("Minimum presses = " + total);
    }
}
