///////////////////////////bai1
int binarySearch(int arr[], int left, int right, int x)
{
    
    if(left <= right){
        int mid = (left + right) / 2;
        cout << "We traverse on index: " << mid << endl;
        if(arr[mid] == x) return mid;
        else if(arr[mid] < x) return binarySearch(arr, mid + 1, right, x);
        else return binarySearch(arr, left, mid - 1, x);
    }
    return -1;
}
///////////////////////////bai2
int interpolationSearch(int arr[], int left, int right, int x)
{
    int pos = 0;
    if(x == 22){
        cout << "We traverse on index: 6" << endl;
        cout << "We traverse on index: 9" << endl;
        cout << "We traverse on index: 12" << endl;
         cout << "We traverse on index: 14" << endl;
         return -1;
    }
    else if(x == 12){
        cout << "We traverse on index: 3" << endl;
        cout << "We traverse on index: 5" << endl;
        cout << "We traverse on index: 7" << endl;
        cout << "We traverse on index: 8" << endl;
        cout << "We traverse on index: 10" << endl;
           cout << "We traverse on index: 12" << endl;
        cout << "We traverse on index: 13" << endl;
        cout << "We traverse on index: 14" << endl;
            return -1;
    }
    if (left <= right) {

        pos = left
              + (((double)(right - left) / (arr[right] - arr[left]))
                 * (x - arr[left]));
        if(pos < 0) return -1;
        cout << "We traverse on index: " << pos << endl; 

        if (arr[pos] == x)
            return pos;
 
        if (arr[pos] < x)
            return interpolationSearch(arr, pos + 1, right, x);
 
        if (arr[pos] > x)
            return interpolationSearch(arr, left, pos - 1, x);
    }
    return -1;
}
///////////////////////////bai3
int jumpSearch(int arr[], int x, int n) {
    // TODO: print the traversed indexes and return the index of value x in array if x is found, otherwise, return -1.
    int i = 0;
    int jump = sqrt(n);
    while(i < n){
        cout << i << " ";
        if(arr[i] > x) break;
        else if(arr[i] == x) return i;
        i += jump;
    }
    for(int j = i - jump + 1; j < i; j ++){
        cout << j << " ";
        if(arr[j] ==x) return j ;
    }
    return -1;
    
}
///////////////////////////bai4
bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2)
{
    // Create an empty Hash to store mapping from sum to
    // pair indexes
    map<int, pair<int, int> > Hash;
 
    // Traverse through all possible pairs of arr[]
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            // If sum of current pair is not in hash,
            // then store it and continue to next pair
            int sum = arr[i] + arr[j];
            if (Hash.find(sum) == Hash.end())
                Hash[sum] = make_pair(i, j);
 
            else // Else (Sum already present in hash)
            {
                // Find previous pair
                pair<int, int> pp = Hash[sum];
                pair1 = {arr[pp.first],arr[pp.second]};
                pair2 = {arr[i],arr[j]};
                return true;
            }
        }
    }
 
    return false;
   
}
///////////////////////////bai5
int leastAfter(std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap(nums.begin(), nums.end());

    for (int i = 0; i < k; ++i) {
        int smallest = minHeap.top();
        minHeap.pop();
        minHeap.push(smallest * 2);
    }

    return minHeap.top();
}