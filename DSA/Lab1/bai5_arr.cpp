// Define the function updateArrayPerRange that takes in a vector of integers nums and a two-dimensional vector of integers operations as parameters.
vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) {
    // Loop through each operation in operations.
    for (vector<int> operation : operations) {
        // Get the values of L, R, and X from the operation.
        int L = operation[0];
        int R = operation[1];
        int X = operation[2];
        // Loop through each element in nums with index in range [L, R] (inclusive).
        for (int i = L; i <= R; i++) {
            // Increase the element by X.
            nums[i] += X;
        }
    }
    // Return the updated nums array.
    return nums;
}
