string minDiffPairs(int* arr, int n) {
    sort(arr, arr + n);
    int minDiff = arr[1] - arr[0];
    for (int i = 2; i < n; i++) {
        minDiff = min(minDiff, arr[i] - arr[i-1]);
    }
    string pairs;
    bool firstPair = true;
    for (int i = 1; i < n; i++) {
        if (arr[i] - arr[i-1] == minDiff) {
            if (!firstPair) {
                pairs += ", ";
            }
            pairs += "(" + to_string(arr[i-1]) + ", " + to_string(arr[i]) + ")";
            firstPair = false;
        }
    }
    return pairs;
}