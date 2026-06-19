bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int low = 0, high = matrixSize - 1;
    while (low <= high) {
        int mid = (high - low) / 2 + low;
        if (matrix[mid][0] <= target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (low == 0) return false;
    else low -= 1;

    int left = 0, right = matrixColSize[low] - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (matrix[low][mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return (left == matrixColSize[low] || matrix[low][left] != target) ? false : true;
}