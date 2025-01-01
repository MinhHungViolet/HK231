int maxNumberOfPeople(vector<int>& rooms, vector<int>& people, int k) {
    int n = people.size();
    int m = rooms.size();
    int ans = 0;
    sort(rooms.begin(), rooms.end());
    sort(people.begin(), people.end());
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (abs(rooms[j] - people[i]) <= k) {
            ans++;
            i++;
            j++;
        } else if (rooms[j] < people[i]) {
            j++;
        } else {
            i++;
        }
    }
    return ans;
}