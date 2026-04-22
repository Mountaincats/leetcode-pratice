bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    char* numset = (char*)malloc(9 * sizeof(char));
    for (int i = 0; i < *boardColSize; i++) {
        numset[i] = 0;
    }

    for (int i = 0; i < *boardColSize; i++) {
        for (int j = 0; j < *boardColSize; j++) {
            if (board[i][j] == '.') continue;
            else if (numset[board[i][j] - '0' - 1] == 1) {
                return false;
            }
            else {
                numset[board[i][j] - '0' - 1] = 1;
            }
        }

        for (int j = 0; j < *boardColSize; j++) {
            numset[j] = 0;
        }
    }

    for (int i = 0; i < *boardColSize; i++) {
        for (int j = 0; j < *boardColSize; j++) {
            if (board[j][i] == '.') continue;
            else if (numset[board[j][i] - '0' - 1] == 1) {
                return false;
            }
            else {
                numset[board[j][i] - '0' - 1] = 1;
            }
        }

        for (int j = 0; j < *boardColSize; j++) {
            numset[j] = 0;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {

                    if (board[r + 3 * i][c + 3 * j] == '.') continue;
                    else if (numset[board[r + 3 * i][c + 3 * j] - '0' - 1] == 1) {
                        return false;
                    }
                    else {
                        numset[board[r + 3 * i][c + 3 * j] - '0' - 1] = 1;
                    }
                }
            }
            for (int j = 0; j < *boardColSize; j++) {
                numset[j] = 0;
            }
        }
    }

    free(numset);
    return true;
}