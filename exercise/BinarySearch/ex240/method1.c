bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target){
    int r = 0, c = *matrixColSize - 1;
    while (r <= matrixSize - 1 && c >= 0) {
        if (matrix[r][c] > target) c--;
        else if (matrix[r][c] < target) r++;
        else return true;
    }

    return false;
}