void dfs(char** grid, int r, int c, int nr, int nc) {
    grid[r][c] = '0';
    if (r - 1 >= 0 && grid[r-1][c] == '1') dfs(grid, r - 1, c, nr, nc);
    if (r + 1 < nr && grid[r+1][c] == '1') dfs(grid, r + 1, c, nr, nc);
    if (c - 1 >= 0 && grid[r][c-1] == '1') dfs(grid, r, c - 1, nr, nc);
    if (c + 1 < nc && grid[r][c+1] == '1') dfs(grid, r, c + 1, nr, nc);
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int nr = gridSize, nc = *gridColSize;

    int island = 0;
    for (int r = 0; r < nr; r++) {
        for (int c = 0; c < nc; c++) {
            if (grid[r][c] == '1') {
                island++;
                dfs(grid, r, c, nr, nc);
            }
        }
    }

    return island;
}