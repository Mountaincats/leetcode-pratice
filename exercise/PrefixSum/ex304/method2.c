typedef struct {
    int col;
    int row;
    int** element;
} NumMatrix;


NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
    NumMatrix* obj = malloc(sizeof(NumMatrix));
    obj->col = *matrixColSize + 1;
    obj->row = matrixSize + 1;

    obj->element = malloc(sizeof(int*) * obj->row);
    obj->element[0] = malloc(sizeof(int) * obj->col);
    memset(obj->element[0], 0, sizeof(int) * obj->col);
    for (int i = 1; i < obj->row; i++) {
        obj->element[i] = malloc(sizeof(int) * obj->col);
        obj->element[i][0] = 0;
    }

    for (int i = 0; i < obj->row - 1; i++) {
        for (int j = 0; j < obj->col - 1; j++) {
            obj->element[i + 1][j + 1] = matrix[i][j] + obj->element[i + 1][j] + obj->element[i][j + 1] - obj->element[i][j];
        }
    }

    return obj;
}

int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
    int r1 = row1 + 1, r2 = row2 + 1, c1 = col1 + 1, c2 = col2 + 1;

    int sum = obj->element[r2][c2] - obj->element[r2][c1 - 1] - obj->element[r1 - 1][c2] + obj->element[r1 - 1][c1 - 1];

    return sum;
}

void numMatrixFree(NumMatrix* obj) {
    for (int i = 0; i < obj->row; i++) {
        free(obj->element[i]);
    }
    free(obj->element);
    free(obj);
}

/**
 * Your NumMatrix struct will be instantiated and called as such:
 * NumMatrix* obj = numMatrixCreate(matrix, matrixSize, matrixColSize);
 * int param_1 = numMatrixSumRegion(obj, row1, col1, row2, col2);
 
 * numMatrixFree(obj);
*/