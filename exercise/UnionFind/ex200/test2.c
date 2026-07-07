#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int r;
    int c;
};

int maxQueueLen = 0;
FILE* logFile = NULL;

int numIslandsWithMaxQueue(char** grid, int gridSize, int* gridColSize) {
    int nr = gridSize, nc = *gridColSize;
    int queueSize = (nr > nc) ? (nc << 1) + 1 : (nr << 1) + 1;
    struct node* queue = malloc(sizeof(struct node) * queueSize);
    int front = 0, rear = 0;

    logFile = fopen("bfs_trace.txt", "w");
    if (logFile == NULL) {
        printf("无法打开日志文件！\n");
        return 0;
    }

    int island = 0;
    for (int r = 0; r < nr; r++) {
        for (int c = 0; c < nc; c++) {
            if (grid[r][c] == '1') {
                island++;
                grid[r][c] = '2';
                queue[rear] = (struct node){r, c};
                rear = (rear + 1) % queueSize;
                
                while (rear != front) {
                    // 计算当前队列长度
                    int currentQueueLen = (rear - front + queueSize) % queueSize;
                    if (currentQueueLen > maxQueueLen) {
                        maxQueueLen = currentQueueLen;
                    }
                    
                    int row = queue[front].r;
                    int col = queue[front].c;
                    grid[row][col] = '0';
                    front = (front + 1) % queueSize;
                    
                    if (row - 1 >= 0 && grid[row - 1][col] == '1') {
                        grid[row - 1][col] = '2';
                        queue[rear] = (struct node){row - 1, col};
                        rear = (rear + 1) % queueSize;
                    }
                    if (row + 1 < nr && grid[row + 1][col] == '1') {
                        grid[row + 1][col] = '2';
                        queue[rear] = (struct node){row + 1, col};
                        rear = (rear + 1) % queueSize;
                    }
                    if (col - 1 >= 0 && grid[row][col - 1] == '1') {
                        grid[row][col - 1] = '2';
                        queue[rear] = (struct node){row, col - 1};
                        rear = (rear + 1) % queueSize;
                    }
                    if (col + 1 < nc && grid[row][col + 1] == '1') {
                        grid[row][col + 1] = '2';
                        queue[rear] = (struct node){row, col + 1};
                        rear = (rear + 1) % queueSize;
                    }

                    // 输出当前队列长度
                    fprintf(logFile, "弹出元素 (%d,%d) 后，队列中元素个数: %d\n", 
                            row, col, currentQueueLen);
                    
                    // 输出当前grid数组
                    for (int i = 0; i < nr; i++) {
                        for (int j = 0; j < nc; j++) {
                            fprintf(logFile, "%c ", grid[i][j]);
                        }
                        fprintf(logFile, "\n");
                    }
                    fprintf(logFile, "\n-----------------------------------------\n");
                }
            }
        }
    }

    if (logFile != NULL) {
        fclose(logFile);
    }
    
    free(queue);
    return island;
}

int main() {
    char data[20][20] = {
        {'1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','0','1','1'},
        {'0','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','0'},
        {'1','0','1','1','1','0','0','1','1','0','1','1','1','1','1','1','1','1','1','1'},
        {'1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
        {'1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
        {'1','0','1','1','1','1','1','1','0','1','1','1','0','1','1','1','0','1','1','1'},
        {'0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','0','1','1'},
        {'1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
        {'0','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1','1','1','1','1'},
        {'1','0','1','1','1','1','1','0','1','1','1','0','1','1','1','1','0','1','1','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','0','0'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
    };

    int rows = 20, cols = 20;

    char** grid = malloc(sizeof(char*) * rows);
    for (int i = 0; i < rows; i++) {
        grid[i] = malloc(cols);
        for (int j = 0; j < cols; j++) {
            grid[i][j] = data[i][j];
        }
    }

    int islandCount = numIslandsWithMaxQueue(grid, rows, &cols);

    printf("网格大小: %d x %d\n", rows, cols);
    printf("岛屿数量: %d\n", islandCount);
    printf("队列中最大元素个数: %d\n", maxQueueLen);
    printf("队列容量: %d\n", (rows > cols) ? (cols << 1) + 1 : (rows << 1) + 1);
    
    int queueCapacity = ((rows > cols) ? (cols << 1) + 1 : (rows << 1) + 1) - 1;
    printf("队列实际可容纳最大元素数: %d\n", queueCapacity);
    
    if (maxQueueLen > queueCapacity) {
        printf("警告：队列溢出！最大元素数超过了队列容量\n");
    } else {
        printf("队列容量充足\n");
    }

    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}