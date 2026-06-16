#define MAX_SIZE 50000
#define EMPTY 0x7f7f7f7f
int key[MAX_SIZE];
int val[MAX_SIZE];

void insert(int f_key)
{
		// 保证索引非负
		// 若 f_key 永远不为负数，则可简化为 f_key % MAX_SIZE
    int idx = (f_key % MAX_SIZE + MAX_SIZE) % MAX_SIZE;
    while (key[idx] != EMPTY)
    {
        if (key[idx] == f_key)
        {
            val[idx]++;
            return;
        }
        idx = (idx + 1) % MAX_SIZE;
    }
    key[idx] = f_key;
    val[idx] = 1;
}

int find(int f_key)
{
    int idx = (f_key % MAX_SIZE + MAX_SIZE) % MAX_SIZE;
    while (key[idx] != EMPTY)
    {
        if (key[idx] == f_key)
        {
            return val[idx];
        }
        idx = (idx + 1) % MAX_SIZE;
    }
    return 0;
}

int subarraySum(int* nums, int numsSize, int k) {
    memset(key, 0x7f, sizeof(int) * MAX_SIZE);
    memset(val, 0, sizeof(int) * MAX_SIZE);

    int sum = 0;
    insert(sum);
    int count = 0;

    for (int i = 0; i < numsSize; i++) {
        sum = sum + nums[i];
        count += find(sum - k);
        insert(sum);
    }

    return count;
}