typedef struct {
    int col;
    int row;
    int** element;
} NumMatrix;


NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
    NumMatrix* obj = malloc(sizeof(NumMatrix));
    obj->col = *matrixColSize;
    obj->row = matrixSize;

    obj->element = malloc(sizeof(int*) * obj->row);

    for (int i = 0; i < obj->row; i++) {
        obj->element[i] = malloc(sizeof(int) * obj->col);
        for (int j = 0; j < obj->col; j++) {
            obj->element[i][j] = matrix[i][j];
        }
    }

    return obj;
}

int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
    int sum = 0;
    for (int i = row1; i <= row2; i++) {
        for (int j = col1; j <= col2; j++) {
            sum += obj->element[i][j];
        }
    }

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