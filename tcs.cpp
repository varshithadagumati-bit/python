import java.util.*;

/**
 * SofaProblem - BFS over (row, col, orientation) states.
 * Orientation: 0 = HORIZONTAL, 1 = VERTICAL
 * Grid tokens: "s", "S", "H", "0"
 */
public class Main {
    static final int H = 0, V = 1;

    static int M, N;
    static char[][] grid; // 's','S','H','0'
    static boolean[][][] visited;

    static class State {
        int r, c, o, d; // row, col (top/left), orientation, distance(steps)
        State(int r, int c, int o, int d) { this.r = r; this.c = c; this.o = o; this.d = d; }
    }

    static boolean inBounds(int r, int c) {
        return r >= 0 && r < M && c >= 0 && c < N;
    }

    static boolean isFree(int r, int c) {
        if (!inBounds(r, c)) return false;
        char ch = grid[r][c];
        return ch == '0' || ch == 's' || ch == 'S';
    }

    // Check if sofa at (r,c,o) fits entirely on free cells
    static boolean fits(int r, int c, int o) {
        if (o == H) {
            return inBounds(r, c) && inBounds(r, c + 1) && isFree(r, c) && isFree(r, c + 1);
        } else {
            return inBounds(r, c) && inBounds(r + 1, c) && isFree(r, c) && isFree(r + 1, c);
        }
    }

    // Check if 2x2 block with top-left at (r,c) is all free
    static boolean block2x2Free(int r, int c) {
        return inBounds(r, c) && inBounds(r + 1, c + 1)
                && isFree(r, c) && isFree(r, c + 1)
                && isFree(r + 1, c) && isFree(r + 1, c + 1);
    }

    // Find orientation and anchor (top/left cell) given two cells
    static int[] anchorAndOrientation(int r1, int c1, int r2, int c2) {
        if (r1 == r2) { // horizontal
            int leftC = Math.min(c1, c2);
            return new int[]{r1, leftC, H};
        } else { // vertical
            int topR = Math.min(r1, r2);
            return new int[]{topR, c1, V}; // c1==c2
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt()) return;
        M = sc.nextInt();
        N = sc.nextInt();
        sc.nextLine();

        grid = new char[M][N];

        List<int[]> starts = new ArrayList<>();     // cells with 's'
        List<int[]> targets = new ArrayList<>();    // cells with 'S'

        for (int i = 0; i < M; i++) {
            // tokens may be space-separated
            String line = sc.nextLine().trim();
            String[] tokens = line.split("\\s+");
            if (tokens.length != N) {
                // fallback: if input is not spaced, treat each char (still robust)
                if (tokens.length == 1 && tokens[0].length() == N) {
                    for (int j = 0; j < N; j++) {
                        grid[i][j] = tokens[0].charAt(j);
                    }
                } else {
                    // If malformed input, try to merge tokens chars
                    int idx = 0;
                    for (String t : tokens) {
                        for (char ch : t.toCharArray()) {
                            if (idx < N) {
                                grid[i][idx++] = ch;
                            }
                        }
                    }
                }
            } else {
                for (int j = 0; j < N; j++) {
                    grid[i][j] = tokens[j].charAt(0);
                }
            }

            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 's') starts.add(new int[]{i, j});
                if (grid[i][j] == 'S') targets.add(new int[]{i, j});
            }
        }

        // Basic validation: we expect exactly two 's' and two 'S'
        if (starts.size() != 2 || targets.size() != 2) {
            System.out.println("Impossible");
            return;
        }

        // Determine start state
        int r1 = starts.get(0)[0], c1 = starts.get(0)[1];
        int r2 = starts.get(1)[0], c2 = starts.get(1)[1];
        if (!areAdjacent(r1, c1, r2, c2)) { System.out.println("Impossible"); return; }
        int[] startInfo = anchorAndOrientation(r1, c1, r2, c2);
        int sr = startInfo[0], scCol = startInfo[1], so = startInfo[2];

        // Determine target state
        int tr1 = targets.get(0)[0], tc1 = targets.get(0)[1];
        int tr2 = targets.get(1)[0], tc2 = targets.get(1)[1];
        if (!areAdjacent(tr1, tc1, tr2, tc2)) { System.out.println("Impossible"); return; }
        int[] goalInfo = anchorAndOrientation(tr1, tc1, tr2, tc2);
        int gr = goalInfo[0], gc = goalInfo[1], go = goalInfo[2];

        visited = new boolean[M][N][2];
        int ans = bfs(sr, scCol, so, gr, gc, go);
        if (ans < 0) System.out.println("Impossible");
        else System.out.println(ans);
    }

    static boolean areAdjacent(int r1, int c1, int r2, int c2) {
        return (r1 == r2 && Math.abs(c1 - c2) == 1) || (c1 == c2 && Math.abs(r1 - r2) == 1);
    }

    static int bfs(int sr, int sc, int so, int gr, int gc, int go) {
        Queue<State> q = new ArrayDeque<>();
        if (!fits(sr, sc, so)) return -1;
        visited[sr][sc][so] = true;
        q.add(new State(sr, sc, so, 0));

        while (!q.isEmpty()) {
            State cur = q.poll();
            if (cur.r == gr && cur.c == gc && cur.o == go) return cur.d;

            // Slide moves
            if (cur.o == H) {
                // left
                if (cur.c - 1 >= 0 && isFree(cur.r, cur.c - 1) && isFree(cur.r, cur.c)) {
                    tryPush(q, cur.r, cur.c - 1, H, cur.d + 1);
                }
                // right
                if (cur.c + 2 - 1 < N && isFree(cur.r, cur.c + 1) && isFree(cur.r, cur.c + 2 - 1)) {
                    tryPush(q, cur.r, cur.c + 1, H, cur.d + 1);
                }
                // up
                if (cur.r - 1 >= 0 && isFree(cur.r - 1, cur.c) && isFree(cur.r - 1, cur.c + 1)) {
                    tryPush(q, cur.r - 1, cur.c, H, cur.d + 1);
                }
                // down
                if (cur.r + 1 < M && isFree(cur.r + 1, cur.c) && isFree(cur.r + 1, cur.c + 1)) {
                    tryPush(q, cur.r + 1, cur.c, H, cur.d + 1);
                }
                // rotations to VERTICAL
                // rotate using 2x2 block above: top-left at (cur.r - 1, cur.c)
                if (cur.r - 1 >= 0 && block2x2Free(cur.r - 1, cur.c)) {
                    tryPush(q, cur.r - 1, cur.c, V, cur.d + 1);
                }
                // rotate using 2x2 block below: top-left at (cur.r, cur.c)
                if (cur.r + 1 < M && block2x2Free(cur.r, cur.c)) {
                    tryPush(q, cur.r, cur.c, V, cur.d + 1);
                }
            } else { // VERTICAL
                // up
                if (cur.r - 1 >= 0 && isFree(cur.r - 1, cur.c)) {
                    tryPush(q, cur.r - 1, cur.c, V, cur.d + 1);
                }
                // down
                if (cur.r + 2 - 1 < M && isFree(cur.r + 2 - 1, cur.c)) {
                    tryPush(q, cur.r + 1, cur.c, V, cur.d + 1);
                }
                // left
                if (cur.c - 1 >= 0 && isFree(cur.r, cur.c - 1) && isFree(cur.r + 1, cur.c - 1)) {
                    tryPush(q, cur.r, cur.c - 1, V, cur.d + 1);
                }
                // right
                if (cur.c + 1 < N && isFree(cur.r, cur.c + 1) && isFree(cur.r + 1, cur.c + 1)) {
                    tryPush(q, cur.r, cur.c + 1, V, cur.d + 1);
                }
                // rotations to HORIZONTAL
                // rotate using 2x2 block to the left: top-left at (cur.r, cur.c - 1)
                if (cur.c - 1 >= 0 && block2x2Free(cur.r, cur.c - 1)) {
                    tryPush(q, cur.r, cur.c - 1, H, cur.d + 1);
                }
                // rotate using 2x2 block to the right: top-left at (cur.r, cur.c)
                if (cur.c + 1 < N && block2x2Free(cur.r, cur.c)) {
                    tryPush(q, cur.r, cur.c, H, cur.d + 1);
                }
            }
        }

        return -1;
    }

    static void tryPush(Queue<State> q, int r, int c, int o, int nd) {
        if (!fits(r, c, o)) return;
        if (!visited[r][c][o]) {
            visited[r][c][o] = true;
            q.add(new State(r, c, o, nd));
        }
    }
}
