typedef struct {
    int* parent;
    int* size;
    int capacity;
    int count;
} UnionFind;

UnionFind* ufInit(int n) {
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->capacity = n;
    uf->parent = (int*)malloc(sizeof(int) * n);
    uf->size = (int*)malloc(sizeof(int) * n);
    uf->count = n;
    
    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
        uf->size[i] = 1;
    }
    return uf;
}

int ufFind(UnionFind* uf, int x) {
    int root = x;
    while (root != uf->parent[root]) {
        root = uf->parent[root];
    }
    while (x != root) {
        int next = uf->parent[x];
        uf->parent[x] = root;
        x = next;
    }
    return root;
}

void ufUnion(UnionFind* uf, int x, int y) {
    int rootX = ufFind(uf, x);
    int rootY = ufFind(uf, y);
    
    if (rootX == rootY) return;
    
    if (uf->size[rootX] < uf->size[rootY]) {
        uf->parent[rootX] = rootY;
        uf->size[rootY] += uf->size[rootX];
    } else {
        uf->parent[rootY] = rootX;
        uf->size[rootX] += uf->size[rootY];
    }
    
    uf->count--;
}

int ufGetCount(UnionFind* uf) {
    return uf->count;
}

void ufFree(UnionFind* uf) {
    free(uf->parent);
    free(uf->size);
    free(uf);
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    if (gridSize == 0 || gridColSize[0] == 0) return 0;
    
    int rows = gridSize;
    int cols = gridColSize[0];
    int totalCells = rows * cols;
    
    UnionFind* uf = ufInit(totalCells);
    
    int landCount = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '1') {
                landCount++;
            } else {
                uf->parent[r * cols + c] = -1;
            }
        }
    }
    
    uf->count = landCount;
    
    int directions[2][2] = {{0, 1}, {1, 0}};
    
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '0') continue;
            
            int current = r * cols + c;
            
            for (int d = 0; d < 2; d++) {
                int nr = r + directions[d][0];
                int nc = c + directions[d][1];
                
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1') {
                    int neighbor = nr * cols + nc;
                    ufUnion(uf, current, neighbor);
                }
            }
        }
    }
    
    int result = ufGetCount(uf);
    
    ufFree(uf);
    
    return result;
}