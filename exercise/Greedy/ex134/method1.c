int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int sum_leave = 0, leave = 0, start = 0;
    for (int i = 0; i < gasSize; i++) {
        leave += gas[i] - cost[i];
        if (leave < 0) {
            start = i + 1;
            sum_leave += leave;
            leave = 0;
        }
    }

    return (leave + sum_leave < 0) ? -1 : start;
}