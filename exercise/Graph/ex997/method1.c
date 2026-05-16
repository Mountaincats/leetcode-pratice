int findJudge(int n, int** trust, int trustSize, int* trustColSize) {
    int indegrees[n];
    int outdegrees[n];
    memset(indegrees, 0, sizeof(indegrees));
    memset(outdegrees, 0, sizeof(outdegrees));
    for (int i = 0; i < trustSize; i++) {
        outdegrees[trust[i][0] - 1]++;
        indegrees[trust[i][1] - 1]++;
    }
    for (int i = 0; i < n; i++) {
        if(indegrees[i] == n - 1 && outdegrees[i] == 0) return i + 1;
    }

    return -1;
}