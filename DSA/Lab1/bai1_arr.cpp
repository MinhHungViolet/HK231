int buyCar(int* nums, int length, int k) {
    // Sort the array in ascending order
    sort(nums, nums + length);
    int count = 0;
    for (int i = 0; i < length; i++) {
        // If the person can afford the car, increment count and subtract the car price from k
        if (nums[i] <= k) {
            count++;
            k -= nums[i];
        }
        // If the person can't afford the car, break the loop
        else {
            break;
        }
    }
    return count;
}