#include <stdio.h>
int main() {
    int r, c;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &r, &c);
    int mat[10][10], tra[10][10];
    printf("Enter elements of the matrix:\n");
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            tra[j][i] = mat[i][j];
        }
    }
    printf("Transpose of the matrix:\n");
    for(int i = 0; i < c; i++) {
        for(int j = 0; j < r; j++) {
            printf("%d ", tra[i][j]);
        }
        printf("\n");
    }

    return 0;
}
