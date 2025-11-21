import java.util.*;

public class Main {
    static final int H = 0, V = 1;
    static int M, N;
    static char[][] grid;
    static boolean[][][] visited;

    static class State {
        int r, c, o, d;
        State(int r, int c, int o, int d) {
            this.r = r; this.c = c; this.o = o; this.d = d;
        }
    }

    static boolean inBounds(int r, int c) {
        return r >= 0 && r < M && c >= 0 && c < N;
    }

    static boolean isFree(int r, int c) {
        if (!inBounds(r, c)) return false;
        char ch = grid[r][c];
        return ch == '0' || ch == 's' || ch == 'S';
    }

    static boolean fits(int r, int c, int o) {
        if (o == H) return inBounds(r, c+1) && isFree(r, c) && isFree(r, c+1);
        else return inBounds(r+1, c) && isFree(r, c) && isFree(r+1, c);
    }

    static boolean block2x2Free(int r, int c) {
        return inBounds(r+1, c+1) &&
               isFree(r,c) && isFree(r,c+1) &&
               isFree(r+1,c) && isFree(r+1,c+1);
    }

    static int[] anchorAndOrientation(int r1, int

