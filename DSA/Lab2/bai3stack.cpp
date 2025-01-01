#include <iostream>
#include <stack>
using namespace std;

class node {
public:
    int x, y;
    int dir;
    node(int i, int j)
    {
        x = i;
        y = j;
        dir = 0;
    }
};

bool canEatFood(int maze[5][5], int fx, int fy) {
    int n = 5;
    int visited[n][n] = {0};
    stack<node> s;
    node temp(0, 0);
    s.push(temp);
    visited[0][0] = 1;
    while (!s.empty()) {
        node top = s.top();
        int x = top.x;
        int y = top.y;
        int dir = top.dir;
        if (x == fx && y == fy) {
            return true;
        }
        if (dir == 0) {
            if (x - 1 >= 0 && maze[x - 1][y] && !visited[x - 1][y]) {
                node temp1(x - 1, y);
                visited[x - 1][y] = 1;
                s.push(temp1);
                break;
            }
            top.dir++;
            s.pop();
            s.push(top);
        }
        else if (dir == 1) {
            if (y - 1 >= 0 && maze[x][y - 1] && !visited[x][y - 1]) {
                node temp1(x, y - 1);
                visited[x][y - 1] = 1;
                s.push(temp1);
                break;
            }
            top.dir++;
            s.pop();
            s.push(top);
        }
        else if (dir == 2) {
            if (x + 1 < n && maze[x + 1][y] && !visited[x + 1][y]) {
                node temp1(x + 1, y);
                visited[x + 1][y] = 1;
                s.push(temp1);
                break;
            }
            top.dir++;
            s.pop();
            s.push(top);
        }
        else if (dir == 3) {
            if (y + 1 < n && maze[x][y + 1] && !visited[x][y + 1]) {
                node temp1(x, y + 1);
                visited[x][y + 1] = 1;
                s.push(temp1);
                break;
            }
            top.dir++;
            s.pop();
            s.push(top);
        }
        else {
            s.pop();
        }
    }
    return false;
}