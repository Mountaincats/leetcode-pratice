struct node {
    int r;
    int c;
};

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int nr = gridSize, nc = *gridColSize;
    int queueSize = (nr > nc) ? (nc << 1) + 1 : (nr << 1) + 1;
    struct node* queue = malloc(sizeof(struct node) * queueSize);
    int front = 0, rear = 0;

    int island = 0;
    for (int r = 0; r < nr; r++) {
        for (int c = 0; c < nc; c++) {
            if (grid[r][c] == '1') {
                island++;
                grid[r][c] = '0';
                queue[rear] = (struct node){r, c};
                rear = (rear + 1) % queueSize;
                while (rear != front) {
                    int row = queue[front].r;
                    int col =  queue[front].c;
                    front = (front + 1) % queueSize;
                    if (row - 1 >= 0 && grid[row - 1][col] == '1') {
                        grid[row - 1][col] = '0';
                        queue[rear] = (struct node){row - 1, col};
                        rear = (rear + 1) % queueSize;
                    }
                    if (row + 1 < nr && grid[row + 1][col] == '1') {
                        grid[row + 1][col] = '0';
                        queue[rear] = (struct node){row + 1, col};
                        rear = (rear + 1) % queueSize;
                    }
                    if (col - 1 >= 0 && grid[row][col - 1] == '1') {
                        grid[row][col - 1] = '0';
                        queue[rear] = (struct node){row, col - 1};
                        rear = (rear + 1) % queueSize;
                    }
                    if (col + 1 < nc && grid[row][col + 1] == '1') {
                        grid[row][col + 1] = '0';
                        queue[rear] = (struct node){row, col + 1};
                        rear = (rear + 1) % queueSize;
                    }
                }
            }
        }
    }

    free(queue);
    return island;
}