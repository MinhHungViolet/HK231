int secondsToBeRotten(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    queue<pair<int, int>> q;
    int freshCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            }
            else if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }
    int time = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            if (x > 0 && grid[x - 1][y] == 1) {
                grid[x - 1][y] = 2;
                q.push({x - 1, y});
                freshCount--;
            }
            if (x < n - 1 && grid[x + 1][y] == 1) {
                grid[x + 1][y] = 2;
                q.push({x + 1, y});
                freshCount--;
            }
            if (y > 0 && grid[x][y - 1] == 1) {
                grid[x][y - 1] = 2;
                q.push({x, y - 1});
                freshCount--;
            }
            if (y < m - 1 && grid[x][y + 1] == 1) {
                grid[x][y + 1] = 2;
                q.push({x, y + 1});
                freshCount--;
            }
        }
        if (!q.empty()) {
            time++;
        }
    }
    return freshCount == 0 ? time : -1;
}