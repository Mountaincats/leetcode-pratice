// 此题的c语言官解有性能bug，由于只在元素出队时才标记已访问，会重复多次在队列中插入相同元素
// 且为了方便没有实现循环队列，空间复杂为实则为 O(n^2) 而非 O(n)
// 修改后如下
int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int cities = isConnectedSize;
    int* visited = calloc(cities, sizeof(int));
    int provinces = 0;
    int* queue = malloc(sizeof(int) * cities);
    int front = 0, rear = 0;

    for (int i = 0; i < cities; i++) {
        if (!visited[i]) {
            queue[rear] = i;
            rear = (rear + 1) % cities;
            visited[i] = 1; // 在入队时就标记
            while (front != rear) {
                int j = queue[front];
                front = (front + 1) % cities;
                for (int k = 0; k < cities; k++) {
                    if (isConnected[j][k] == 1 && !visited[k]) {
                        queue[rear] = k;
                        rear = (rear + 1) % cities;
                        visited[k] = 1; // 在入队时就标记
                    }
                }
            }
            provinces++;
        }
    }

    free(visited);
    free(queue);
    return provinces;
}