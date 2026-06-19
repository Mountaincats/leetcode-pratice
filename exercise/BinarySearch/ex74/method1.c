bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int l = 0, r = matrixSize * (*matrixColSize) - 1;

    while (l <= r) {
        int m = (l + r) / 2;
        if (matrix[m / *matrixColSize][m % *matrixColSize] < target) {
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }


    return (l / *matrixColSize == matrixSize || matrix[l / *matrixColSize][l % *matrixColSize] != target) ? false : true;
}