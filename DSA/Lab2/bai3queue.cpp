long long nthNiceNumber(int n) {
    queue<long long> q;
    q.push(2);
    q.push(5);
    long long num = 0;
    for (int i = 1; i <= n; i++) {
        num = q.front();
        q.pop();
        q.push(num * 10 + 2);
        q.push(num * 10 + 5);
    }
    return num;
}