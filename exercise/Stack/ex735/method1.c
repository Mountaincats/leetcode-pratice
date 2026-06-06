/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* asteroidCollision(int* asteroids, int asteroidsSize, int* returnSize) {
    int* result = malloc(sizeof(int) * asteroidsSize);
    int top = -1;
    for (int i = 0; i < asteroidsSize; i++) {
        if (top == -1 || result[top] < 0 || asteroids[i] > 0) result[++top] = asteroids[i];
        else {
            if (result[top] > -asteroids[i]) continue;
            else if (result[top] < -asteroids[i]) {
                top--;
                i--;
            }
            else {
                top--;
            }
        }
    }

    *returnSize = top + 1;

    return result;
}