#include <stdio.h>
#include <stdbool.h>
#include <math.h>


#define EPS (1e-6)
#define N (100)
#define M (100)
#define SUCCESS (0)
#define ERROR (1)
#define DUAL (2)

double zero_by_threshold(double num, double eps) {
    return fabs(num) > eps ? num : 0;
}
// Input: pointer for matrix sizes (m,n)
// Output: did the function succeed in getting matrix size as input (and a valid size)?
bool read_sizes(int * n, int * m) {
    if (scanf("%d%d", n, m) != DUAL) {
        return false;
    }

    return ((*n >= 1) && (*n <= N) && (*m >= 1) && (*m <= M));
}

void print_matrix(double a[][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%.2f ", zero_by_threshold(a[i][j], EPS));
        }

        printf("\n");
    }

    printf("\n");
}
// Input: matrix and matrix size
// Output: did the function succeed getting matrix values as input?
// The function gets input values and puts them in the matrix.
bool read_matrix(double a[][M], int n, int m) {
    int i = 0, j = 0;
    double input = 0;
    while(scanf("%lf", &input) == 1)
    {
        a[i][j] = input;
        j++;
        if(j >= m){
            i++;
            if(i < n)
                j = 0;
            else if(i > n)
                return false;
        }

    }
    return  i == n && j == m;
}
// Input: matrix, the matrix size, two rows indexes
// The function swaps the two rows in the matrix
void swap_rows(double a[][M], int n, int m, int row1, int row2) {
    n = n;
    int temp = 0;
    for(int i = 0; i < m; i++)
    {
        temp = a[row1][i];
        a[row1][i] = a[row2][i];
        a[row2][i] = temp;
    }
}
// Input: matrix, the matrix size, row index and a long float scalar
// The function multiplies the row given with the index by the given scalar
void multiply_row(double a[][M], int n, int m, int row, double scalar) {
    n = n;
    for(int i = 0; i < m; i++)
        a[row][i] *= scalar;
}
// Input: matrix, the matrix size, two rows indexes and a long float scalar
// The function adds the first row with the second row multiplied by the given scalar
void add_row_to_row(double a[][M], int n, int m, int row1, int row2, double scalar) {
    n = n;
    for(int i = 0; i < m; i++)
        a[row1][i] += scalar * a[row2][i];
}
// Input: matrix, the matrix size, two pointers for row and column and the starting row called 'iteration'
// The function finds the leading element starting from the given iteration
bool find_leading_element(double a[][M], int n, int m, int * row, int * column) {
    if(!n)
        return false;
    for(int j = 0; j < m; j++)
    {
        for(int i = 0; i < n; i++)
        {
            if(zero_by_threshold(a[i][j],EPS))
            {
                *(row) = i;
                *(column) = j;
                return true;
            }
        }
    }
    return false;
}
// Input: the matrix and it's size
// The function reduces the rows of the matrix to an ordered matrix
void reduce_rows(double a[][M], int n, int m) {
    int row = 0, col = 0, iteration = 0;
    while(find_leading_element((a + iteration), n - iteration, m,
                                &row, &col))
    {
        row += iteration;
        if(row != iteration)
            swap_rows(a, n, m, row, iteration);

        multiply_row(a, n, m, iteration, 1/a[iteration][col]);
        for(int i = iteration + 1; i < n; i++)
        {
            add_row_to_row(a, n, m, i, iteration, -a[i][col]);
        }

        iteration++;
    }
}

int main() {
    int n;
    int m;
    //
    printf("Enter matrix size (row and column numbers): ");
    if (!read_sizes(&n, &m)) {
        printf("Invalid sizes!\n");
        return ERROR;
    }

    int a[N][M];
    printf("Enter matrix:\n");
    if (!read_matrix((double (*)[M]) a, n, m)) {
        printf("Invalid matrix!\n");
        return ERROR;
    }

    reduce_rows((double (*)[M]) a, n, m);
    printf("The reduced matrix:\n");
    print_matrix((double (*)[M]) a, n, m);
    return SUCCESS;
}
